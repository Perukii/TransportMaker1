#include "cairo_picker/src/cairo_picker.hpp"
#include "RTree/RTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

#define DATA_READER_MODE_STRING

#include "DataReader/data_reader.cpp"
#include "public.cpp"
#include "input.cpp"
#include "dbscan.cpp"
#include "a_star.cpp"
#include "utility.cpp"

A_star::path_container path_cont;

#include "draw.cpp"

void prepare_data(){
    
    const char * file = "resources/Hokkaido_0.txt";
    Data_reader::data_container data_cont;
    Data_reader::read_data(data_cont, file);
    
    for(auto it:data_cont){
        Public::city_points.push_back({
            it[0].c_str(),
            Data_reader::string_to_double(it[1]),
            Data_reader::string_to_double(it[2]),
            Data_reader::string_to_double(it[3]), -1});
        if(Public::city_points.back().population <= 0) Public::city_points.pop_back();
    }

    std::sort(Public::city_points.begin(),Public::city_points.end(),
        [](Public::city_info a, Public::city_info b){ return a.population > b.population; });

    Public::max_city_range = Public::city_range_f(Public::city_points[0].population);

    for(int i=0; i<Public::city_points.size(); i++){
        const double pa[2]={Public::city_points[i].x, Public::city_points[i].y};
        Public::rdata.Insert(pa, pa, i);
    }
    for(int i=0; i<Public::city_points.size(); i++){
        Dbscan::cluster(Public::rdata, Public::city_points, i, -1);
    }

    //std::cout<<Public::max_city_range<<std::endl;
}

double debug_path(std::string str, std::string end, double cell_wide){
    return A_star::a_star_search(path_cont, get_city_location(str), get_city_location(end), cell_wide);
}

int main(){
    
    const char* map_name = "resources/Hokkaido_0.png";
    Public::base.open_file(map_name);
    prepare_data();

    debug_path("Sapporo","Asahikawa", 5.0);
    debug_path("Wakkanai","Asahikawa", 5.0);
    debug_path("Kitami","Asahikawa", 5.0);
    
    //std::cout<<A_star::a_star_search(path_cont, get_city_location("Sapporo"), get_city_location("Asahikawa"), 10.0)<<std::endl;
    //std::cout<<A_star::a_star_search(path_cont, get_city_location("Asahikawa"), get_city_location("Obihiro"), 1.0)<<std::endl;
    //std::cout<<A_star::a_star_search(path_cont, get_city_location("Sapporo"), get_city_location("Hakodate"), 2.0)<<std::endl;
    //std::cout<<A_star::a_star_search(path_cont, get_city_location("Ebetsu"), get_city_location("Hurano"), 1.0)<<std::endl;
    //std::cout<<A_star::a_star_search(path_cont, get_city_location("Tomakomai"), get_city_location("Obihiro"), 3.0)<<std::endl;
    

    Public::picker.set_default_size(Public::base.w()*Public::pixel_adj, Public::base.h()*Public::pixel_adj);
    Public::picker.set_loop(10);
    Public::picker.set_button_input(bpress, NULL);
    Public::picker.set_motion_input(motion);
    Public::picker.set_title(map_name);
    Public::picker.run(func);
}