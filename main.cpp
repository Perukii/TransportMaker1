#include "cairo_picker/src/cairo_picker.hpp"
#include <iostream>
#include <vector>

#define DATA_READER_MODE_STRING

#include "DataReader/data_reader.cpp"
#include "public.cpp"
#include "input.cpp"
#include "a_star.cpp"
#include "dbscan.cpp"
#include "utility.cpp"

A_star::path_container path_cont;

#include "draw.cpp"

void prepare_data(){
    
    const char * file = "resources/Hokkaido_0.txt";
    Data_reader::data_container data_cont;
    Data_reader::read_data(data_cont, file);
    
    for(auto it:data_cont){
        std::cout<<it[0]<<";"<<std::endl;
        Public::city_points.push_back({
            it[0].c_str(),
            Data_reader::string_to_double(it[1]),
            Data_reader::string_to_double(it[2]),
            Data_reader::string_to_double(it[3]), -1});
    }
}

int main(){
    
    const char* map_name = "resources/Hokkaido_0.png";
    Public::base.open_file(map_name);
    Dbscan::r_tree rdata;
    prepare_data();

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