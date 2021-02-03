namespace Public{
    Capr::C_picker picker;
    Capr::Function::C_picture base;
    const double pixel_adj = 0.2;
    const int max_step = 100000;

    const double hundred_km_to_pixel = 900; 
    const double city_range_size = 0.10; // 1.0 -> 100km
    const double height_diff_weight_up = 1.5;
    const double height_diff_weight_down = 1.5;
    const double height_weight = 2.0;
    const double city_pass_weight = 3.0;

    double city_scale_f(double population){
        return std::log(population)/std::log(10'000);
    }
    double city_range_f(double population){
        return city_scale_f(population)*city_range_size*hundred_km_to_pixel;
    }
    //const double length_weight = 1.0;
    

    struct city_info{
        std::string name;
        double x;
        double y;
        double population;
        int class_num = -1;
    };

    struct cursor{
        double x,y;
    };

    cursor cursor_info;
    double max_city_range;

    using city_info_cont = std::vector<city_info>;
    using r_tree = RTree<int, double, 2, double>;

    std::vector<std::vector<int>> city_points_class;

    city_info_cont city_points;
    r_tree rdata;
    
}
