
A_star::c_point get_city_location(const std::string tar){
    for(int i=0;i<Public::city_points.size();i++){
        if(Public::city_points[i].name == tar) return A_star::c_point{Public::city_points[i].x,Public::city_points[i].y};
    }
    return A_star::c_point{0,0};
}