#include "cairo_picker/src/cairo_picker.hpp"
#include <iostream>
#include <cmath>
#include "public.cpp"
#include "input.cpp"
#include "a_star.cpp"
#include "dbscan.cpp"

A_star::path_container path_cont;

#include "draw.cpp"


A_star::c_point get_city_location(const char* tar){
    for(int i=0;i<Public::city_points.size();i++){
        if(Public::city_points[i].name == tar)return A_star::c_point{Public::city_points[i].x,Public::city_points[i].y};
    }
    return A_star::c_point{0,0};
}

int main(){
    
    const char* map_name = "resources/Hokkaido_0.png";
    Public::base.open_file(map_name);
    Dbscan::r_tree rdata;

    Public::city_points.push_back({"Sapporo"  ,2160 ,2720 ,1'958'408, -1});
    Public::city_points.push_back({"Ebetsu"   ,2270 ,2700 ,119'409 , -1});
    Public::city_points.push_back({"Otaru"    ,1920 ,2640 ,113'728 , -1});
    Public::city_points.push_back({"Tomakomai",2320 ,3130 ,170'555 , -1});
    Public::city_points.push_back({"Obihiro"  ,3490 ,2870 ,165'384 , -1});
    Public::city_points.push_back({"Kushiro"  ,4380 ,2800 ,166'573 , -1});
    Public::city_points.push_back({"Asahikawa",2890 ,2050 ,332'610 , -1});

    for(int i=0; i<Public::city_points.size(); i++){
        const double pa[2]={Public::city_points[i].x, Public::city_points[i].y};
        rdata.Insert(pa, pa, i);
    }
    for(int i=0; i<Public::city_points.size(); i++){
        Dbscan::cluster(rdata, Public::city_points, i, -1);
    }
    std::cout<<A_star::a_star_search(path_cont, get_city_location("Sapporo"), get_city_location("Asahikawa"), 1.0)<<std::endl;
    std::cout<<A_star::a_star_search(path_cont, get_city_location("Asahikawa"), get_city_location("Obihiro"), 1.0)<<std::endl;
    


    Public::picker.set_default_size(Public::base.w()*Public::pixel_adj, Public::base.h()*Public::pixel_adj);
    Public::picker.set_loop(0);
    Public::picker.set_button_input(bpress, NULL);
    Public::picker.set_title(map_name);
    Public::picker.run(func);
}