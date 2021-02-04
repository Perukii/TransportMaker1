namespace Public{

    double city_scale_f(double population){
        return std::log(population)/std::log(10'000);
    }
    double city_range_f(double population){
        return city_scale_f(population)*city_scale_f(population)*city_range_size*hundred_km_to_pixel;
    }

    double debug_path(A_star::path_container* path_cont, std::string str, std::string end, double cell_width){
        return A_star::a_star_search(path_cont, Utility::get_city_location(str), Utility::get_city_location(end), cell_width);
    }

    double debug_path(A_star::path_container* path_cont, int str, int end, double cell_width){
        return A_star::a_star_search(path_cont,
            A_star::c_point{Public::city_points[str].x,Public::city_points[str].y},
            A_star::c_point{Public::city_points[end].x,Public::city_points[end].y},
            cell_width);
    }
}
