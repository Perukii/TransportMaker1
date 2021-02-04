
void bpress(uint button, uint x, uint y){
    //std::cout<<int(x/Public::pixel_adj)<<","<<int(y/Public::pixel_adj)<<","<<button<<std::endl;
    if(button == 2){
        Public::picker.write_to_png("resources/Hokkaido_0_Result.png");
    }
}

void motion(uint x, uint y){
    Public::cursor_info = {double(x),double(y)};
    
}