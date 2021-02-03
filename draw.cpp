
#include <random>

int city_class(int population){
    if(population >= 1'000'000) return 2;
    else if(population >= 300'000) return 1;
    else return 0;
}

void func(Capr::Cairo_cont cr){
    Public::base.set_picture(cr, 0, 0, Public::base.w()*Public::pixel_adj, Public::base.h()*Public::pixel_adj);
    cr->paint();

    for(int ix = Public::hundred_km_to_pixel*Public::pixel_adj/2; ix<Public::base.w()*Public::pixel_adj; ix+=Public::hundred_km_to_pixel*Public::pixel_adj){
        
        cr->set_source_rgba(0.2,0.2,0.2,0.5);
        cr->set_line_width(0.3);

        cr->move_to(ix,0);
        cr->line_to(ix,Public::picker.h());
        cr->stroke();
        cr->move_to(0,ix);
        cr->line_to(Public::picker.w(),ix);
        cr->stroke();

    }

    const double mark_size_base = 5;

    struct color{double r,g,b;};
    color cset[] = {{0.5,0.5,0.5},{1.0, 0.5, 0.5}};

    std::set<int> found_class;
    for(int i=0;i<Public::city_points.size();i++){
        if(std::pow(Public::cursor_info.x/Public::pixel_adj-Public::city_points[i].x,2)+
            std::pow(Public::cursor_info.y/Public::pixel_adj-Public::city_points[i].y,2)
            <= std::pow(Public::city_range_f(Public::city_points[i].population),2)){
                found_class.insert(Public::city_points[i].class_num);
        }
    }

    for(int i=0;i<Public::city_points.size();i++){
        const int cset_ad = found_class.find(Public::city_points[i].class_num) != found_class.end();
        const double stroke_color = 0.3;
        const double pp_log = Public::city_range_f(Public::city_points[i].population);
        const double mark_size = mark_size_base*Public::city_scale_f(Public::city_points[i].population);
        const double range_size = Public::pixel_adj*pp_log;

        cr->set_source_rgba(cset[cset_ad].r,cset[cset_ad].g,cset[cset_ad].b, 0.5);
        cr->arc(Public::city_points[i].x*Public::pixel_adj, Public::city_points[i].y*Public::pixel_adj, range_size, 0, 2*M_PI);
        cr->fill();

        cr->set_source_rgb(cset[cset_ad].r,cset[cset_ad].g,cset[cset_ad].b);
        cr->rectangle(Public::city_points[i].x*Public::pixel_adj-mark_size/2, Public::city_points[i].y*Public::pixel_adj-mark_size/2, mark_size, mark_size);
        cr->fill_preserve();

        cr->set_line_width(city_class(Public::city_points[i].population)+1);
        cr->set_source_rgb(cset[cset_ad].r*stroke_color,cset[cset_ad].g*stroke_color,cset[cset_ad].b*stroke_color);
        cr->stroke();
    }



    for(int i=0;i<path_cont.size();i++){
        cr->move_to(path_cont[i][0].x*Public::pixel_adj,path_cont[i][0].y*Public::pixel_adj);
        for(int j=1;j<path_cont[i].size();j++){
            cr->line_to(path_cont[i][j].x*Public::pixel_adj,path_cont[i][j].y*Public::pixel_adj);
        }
    }

    cr->set_line_width(1);
    cr->set_source_rgb(1.0,0.2,0.2);
    cr->stroke();


}