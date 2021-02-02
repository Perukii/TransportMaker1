#include "cairo_picker/src/cairo_picker.hpp"
#include <iostream>
#include <cmath>
#include "public.cpp"
#include "input.cpp"
#include "a_star.cpp"
#include "dbscan.cpp"

A_star::path_container path_cont;

#include "draw.cpp"


int main(){
    
    const char* map_name = "resources/Map1.png";
    Public::base.open_file(map_name);

    Public::city_points.push_back({"city0", 585, 1162, 1'000'000, -1});
    Public::city_points.push_back({"city1", 552, 1120, 300'000  , -1}); 
    Public::city_points.push_back({"city2", 642, 325 , 50'000   , -1}); 
    Public::city_points.push_back({"city3", 1335,850 , 700'000  , -1}); 
    Public::city_points.push_back({"city4", 982, 1205, 120'000  , -1}); 

    Dbscan::r_tree rdata;

    for(int i=0; i<Public::city_points.size(); i++){
        const double pa[2]={Public::city_points[i].x, Public::city_points[i].y};
        rdata.Insert(pa, pa, i);
    }

    for(int i=0; i<Public::city_points.size(); i++){
        Dbscan::cluster(rdata, Public::city_points, i, -1);
    }
    
    std::cout<<A_star::a_star_search(path_cont, A_star::c_point{642,325}, A_star::c_point{1335,850}, 10)<<std::endl;

    Public::picker.set_default_size(Public::base.w()*Public::pixel_adj, Public::base.h()*Public::pixel_adj);
    Public::picker.set_loop(0);
    Public::picker.set_button_input(bpress, NULL);
    Public::picker.set_title(map_name);
    Public::picker.run(func);
}