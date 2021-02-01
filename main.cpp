#include "cairo_picker/src/cairo_picker.hpp"
#include <iostream>

Capr::C_picker picker;
Capr::Function::C_picture base;
const double
    dp = 0.4
;

#include "input.cpp"
#include "a_star.cpp"


void func(Capr::Cairo_cont cr){
    base.set_picture(cr, 0, 0, base.w()*dp, base.h()*dp);
    cr->paint();
}


int main(){
    
    const char* map_name = "resources/Map1.png";
    base.open_file(map_name);

    picker.set_default_size(base.w()*dp, base.h()*dp);
    picker.set_loop(0);
    picker.set_button_input(bpress, NULL);
    picker.set_title(map_name);
    picker.run(func);
}