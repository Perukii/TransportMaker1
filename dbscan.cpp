#include "RTree/RTree.h"


namespace Dbscan{

    using r_tree = RTree<int, double, 2, double>;

    
    const int minsize = 2;
    int latest_class_num = 0;

    void cluster(r_tree& rdata, Public::city_info_cont& data, int core, int core_class_num){

        if(data[core].class_num != -1) return;
        const double distance = 2*Public::hundred_km_to_pixel*Public::city_range_size*std::sqrt(data[core].population)*0.001;

        const double
            rmin[2]= {data[core].x-distance, data[core].y-distance},
            rmax[2]= {data[core].x+distance, data[core].y+distance};

        std::vector<int> list = {};

        std::function<bool(const int&)> func = 
            [&](const int num){
                if((data[num].x-data[core].x)*(data[num].x-data[core].x)+(data[num].y-data[core].y)*(data[num].y-data[core].y) <= distance*distance)
                    list.push_back(num);
                return true;
            };

        rdata.Search(rmin, rmax, func);

        
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
