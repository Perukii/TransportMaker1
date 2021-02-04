
namespace Kruskal{
    struct path_data{
        int str,end;
        double cost;
    };

    bool operator<(const path_data& a, const path_data& b){
        return a.cost<b.cost;
    }

    std::vector<int> city_points_uftag;

    int uftag_root(int i){
        if(city_points_uftag[i] == i) return i;
        else return uftag_root(city_points_uftag[i]);
    }

    void kruskal(std::vector<path_data>* extracted_path){

        std::set<path_data> path_data_table;
        int class_num = Public::city_points_class.size();

        std::vector<std::vector<double>> path_result(class_num,std::vector<double>(class_num,0));
        city_points_uftag = std::vector<int>(class_num);
        
        auto target_city = [&](int i){ return Public::city_points[Public::city_points_class[i][0]];};

        for(int i=0;i<class_num;i++){
            for(int j=i+1;j<class_num;j++){
                
                double cost = Public::debug_path(NULL, Public::city_points_class[i][0], Public::city_points_class[j][0], Public::kruskal_cell_width);
                double average_population = std::pow(Public::max_population/(0.5*(target_city(i).population+target_city(j).population)),Public::kruskal_average_population_weight);
                double result = cost*average_population;
                path_data_table.insert({i,j,result});
                path_result[i][j] = -result;
            }
            city_points_uftag[i] = i;
        }

        for(auto it=path_data_table.begin(); it!=path_data_table.end();it++){

            bool accept = false;

            if(uftag_root(it->str) == uftag_root(it->end)){
                //if()
                //std::vector<double> d_cost_sum(class_num, -1);
                std::multimap<double, int> d_open;
                std::set<int> d_close;
                d_open.emplace(0, it->str);
                bool loop = true;
                double result_cost;
                //d_cost_sum[it->str] = 0;

                while(loop){
                    auto jt = d_open.begin();

                    for(int i=0;i<class_num;i++){
                        if(d_close.find(i) != d_close.end())continue;
                        double path_cost = i < jt->second ? path_result[i][jt->second]:path_result[jt->second][i];
                        if(path_cost > 0){
                            d_open.emplace(jt->first + path_cost, i);
                            if(i == it->end){
                                loop = false;
                                result_cost = jt->first + path_cost;
                            }
                        }
                    }
                    d_close.insert(jt->second);
                    d_open.erase(jt);
                }

                double compare_cost = std::abs(path_result[it->str][it->end]);

                if(compare_cost < result_cost*Public::cycle_accept_probablity){
                    accept = true;
                }

            }
            else{
                city_points_uftag[uftag_root(it->str)] = uftag_root(it->end);

                accept = true;
            }

            if(accept){
                if(extracted_path != NULL) extracted_path->push_back(
                    {
                    Public::city_points_class[it->str][0],
                    Public::city_points_class[it->end][0],
                    it->cost});

                path_result[it->str][it->end] = std::abs(path_result[it->str][it->end]);
            }
        }

    }
};