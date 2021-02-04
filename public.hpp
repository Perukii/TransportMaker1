namespace Public{
    Capr::C_picker picker;
    Capr::Function::C_picture base;
    const double pixel_adj = 0.2;
    const int max_step = 1000000;

    const double hundred_km_to_pixel = 900; 
    const double city_range_size = 0.045; // 1.0 -> 100km
    const double height_diff_weight_up = 2.5;
    const double height_diff_weight_down = 2.5;
    const double height_weight = 1.0;
    const double city_pass_weight = 2.0;
    const double kruskal_cell_width = 20.0;
    const double kruskal_average_population_weight = 0.2;
    const double cycle_accept_probablity = 0.5;

    double city_scale_f(double population);
    double city_range_f(double population);
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
    double max_population;

    using city_info_cont = std::vector<city_info>;
    using r_tree = RTree<int, double, 2, double>;

    std::vector<std::vector<int>> city_points_class;
    city_info_cont city_points;
    r_tree rdata;


    //double debug_path(A_star::path_container* path_cont, std::string str, std::string end, double cell_wide);

    
}
