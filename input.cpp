
void bpress(uint button, uint x, uint y){
    std::cout<<int(x/Public::pixel_adj)<<","<<int(y/Public::pixel_adj)<<","<<button<<std::endl;
}

void motion(uint x, uint y){
    Public::cursor_info = {double(x),double(y)};
}