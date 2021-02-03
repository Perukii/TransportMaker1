

namespace Dbscan{

    const int minsize = 2;
    int latest_class_num = 0;

    void rtree_search(Public::r_tree& rdata, Public::city_info_cont& data, double x, double y, std::vector<int>& list, double distance){

        const double
            rmin[2]= {x-distance, x-distance},
            rmax[2]= {x+distance, y+distance};

        std::function<bool(const int&)> func = 
            [&](const int num){
                if(std::pow(data[num].x-x,2)+std::pow(data[num].y-y,2) <= distance*distance)
                    list.push_back(num);
                return true;
            };

        rdata.Search(rmin, rmax, func);
    }

    void rtree_search_for_dbscan(Public::r_tree& rdata, Public::city_info_cont& data, int core, std::vector<int>& list){
        
        const double distance = Public::city_range_f(data[core].population);

        const double
            rmin[2]= {data[core].x-distance*2, data[core].y-distance*2},
            rmax[2]= {data[core].x+distance*2, data[core].y+distance*2};

        std::function<bool(const int&)> func = 
            [&](const int num){
                if(std::pow(data[num].x-data[core].x,2)+std::pow(data[num].y-data[core].y,2) <= std::pow(distance+Public::city_range_f(data[num].population),2))
                    list.push_back(num);
                return true;
            };

        rdata.Search(rmin, rmax, func);

    }

    void cluster(Public::r_tree& rdata, Public::city_info_cont& data, int core, int core_class_num){

        if(data[core].class_num != -1) return;

        std::vector<int> list = {};

        rtree_search_for_dbscan(rdata, data, core, list);
        
        if(core_class_num == -1 or list.size() < minsize){
            data[core].class_num = latest_class_num;
            latest_class_num++;
        }
        else{
            data[core].class_num = core_class_num;
        }

        for(int it:list){
            cluster(rdata, data, it, data[core].class_num);
        }
        
        
    }

};
