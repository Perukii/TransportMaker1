namespace Public{
    Capr::C_picker picker;
    Capr::Function::C_picture base;
    const double pixel_adj = 0.4;
    const double hundred_km_to_pixel = 800; 
    const double city_range_size = 0.15; // 1.0 -> 100km

    struct city_info{
        const char* name;
        double x;
        double y;
        double population;
        int class_num = -1;

    };

    using city_info_cont = std::vector<city_info>;

    city_info_cont city_points;


    
}
