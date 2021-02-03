namespace Public{
    Capr::C_picker picker;
    Capr::Function::C_picture base;
    const double pixel_adj = 0.2;
    const int max_step = 50000;

    const double hundred_km_to_pixel = 900; 
    const double city_range_size = 0.20; // 1.0 -> 100km
    const double height_diff_weight_up = 2.5;
    const double height_diff_weight_down = 1.0;
    //const double height_weight = 1.0;
    //const double length_weight = 1.0;
    

    struct city_info{
        std::string name;
        double x;
        double y;
        double population;
        int class_num = -1;

    };

    using city_info_cont = std::vector<city_info>;

    city_info_cont city_points;


    
}
