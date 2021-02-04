#include "cairo_picker/src/cairo_picker.hpp"
#include "RTree/RTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

#define DATA_READER_MODE_STRING

#include "DataReader/data_reader.cpp"
#include "public.hpp"
#include "input.cpp"
#include "dbscan.cpp"
#include "a_star.cpp"
#include "utility.cpp"
#include "public.cpp"
#include "kruskal.cpp"

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

    auto city_sort_func = [](Public::city_info a, Public::city_info b){ return a.population > b.population; };

    std::sort(Public::city_points.begin(),Public::city_points.end(),city_sort_func);

    Public::max_city_range = Public::city_range_f(Public::city_points[0].population);
    Public::max_population = Public::city_points[0].population;

    for(int i=0; i<Public::city_points.size(); i++){
        const double pa[2]={Public::city_points[i].x, Public::city_points[i].y};
        Public::rdata.Insert(pa, pa, i);
    }
    for(int i=0; i<Public::city_points.size(); i++){
        Dbscan::cluster(Public::rdata, Public::city_points, i, -1);
    }

    for(int i=0; i<Public::city_points.size(); i++){
        if(Public::city_points[i].class_num < 0) continue;
        while(Public::city_points[i].class_num >= Public::city_points_class.size()){
            Public::city_points_class.push_back({});
        }
        Public::city_points_class[Public::city_points[i].class_num].push_back(i);
    }

    for(int i=0; i<Public::city_points_class.size(); i++){
        std::sort(Public::city_points_class[i].begin(),Public::city_points_class[i].end(),[&](int a, int b){
            return Public::city_points[a].population > Public::city_points[b].population;
        });
        //std::cout<<Public::city_points[Public::city_points_class[i][0]].name<<std::endl;
    }
}



int main(){
    
    const char* map_name = "resources/Hokkaido_0.png";
    Public::base.open_file(map_name);
    prepare_data();

    //Public::debug_path(&path_cont, 0, 1, 5.0);
    //Public::debug_path(&path_cont,"Hakodate","Muroran", 70.0);
    //Public::debug_path(&path_cont,"Kitami","Asahikawa", 5.0);
    //Public::debug_path(&path_cont,"Obihiro","Asahikawa", 5.0);

    std::vector<Kruskal::path_data> extracted_path;
    std::cout<<"Preparing..."<<std::endl;
    Kruskal::kruskal(&extracted_path);
    std::cout<<"Routes generated"<<std::endl<<"Tracking routes..."<<std::endl;
    for(int i=0;i<extracted_path.size();i++){
        std::cout<<"Route:("<<i<<"/"<<extracted_path.size()<<"), "<<Public::city_points_class.size()<<std::endl;
        Public::debug_path(&path_cont, extracted_path[i].str, extracted_path[i].end, 2.0);
    }
    

    Public::picker.set_default_size(Public::base.w()*Public::pixel_adj, Public::base.h()*Public::pixel_adj);
    Public::picker.set_loop(10);
    Public::picker.set_button_input(bpress, NULL);
    Public::picker.set_motion_input(motion);
    Public::picker.set_title(map_name);
    Public::picker.run(func);
}