

namespace A_star{

    const int max_step = 50000;

    struct c_point{
        double x = 0,y = 0;
    };

    struct c_point_comp{
        c_point parent;
        c_point point;
        double cost = 0;
    };

    struct c_color{
        int r;
        int g;
        int b;
    };

    using path_container = std::vector<std::vector<c_point>>;

    bool operator<(const c_point& a, const c_point& b){
        return 
            std::floor(a.y)<std::floor(b.y)
            or (std::floor(a.y)==std::floor(b.y) and std::floor(a.x)<std::floor(b.x));
    }

    bool operator==(const c_point& a, const c_point& b){
        return 
            std::floor(a.y)==std::floor(b.y) and std::floor(a.x)==std::floor(b.x);
    }

    bool operator<(const c_point_comp& a, const c_point_comp& b){
        return a.point<b.point;
    }

    c_color get_color(double x, double y){
        auto data = Public::base.get_pixel(x/Public::pixel_adj, y/Public::pixel_adj);
        return c_color{int(data[0]),int(data[1]),int(data[2])};
    }

    c_color get_color(c_point pt){
        return get_color(pt.x, pt.y);
    }

    double euc(c_point pfrom, c_point pto){
        return std::sqrt(std::pow(pfrom.x-pto.x,2)+std::pow(pfrom.y-pto.y,2));
    }

    double get_cost(c_point pfrom, c_point pto, c_point _parent){
        double dist = std::abs(get_color(pfrom).g-get_color(pto).g);
        double result = (1+dist)*(std::max(std::abs(pfrom.x-pto.x), std::abs(pfrom.y-pto.y))*std::pow(euc(pfrom,_parent),0.5));
        return result;
    }

    double a_star_search(path_container& path, c_point pst, c_point ptr, double cell_wide){

        pst.x *= Public::pixel_adj;
        pst.y *= Public::pixel_adj;
        ptr.x *= Public::pixel_adj;
        ptr.y *= Public::pixel_adj;

            
        std::set<c_point_comp> open;
        std::set<c_point_comp> close;
        open.insert(c_point_comp{pst, pst, 0});
        auto center_ptr = open.begin();
        c_point center;
        double cost;

        int step = 0;

        while((step++)<max_step){
            center_ptr = open.begin();
            
            cost = -1; 
            for(auto it = open.begin(); it != open.end(); it++){
                double cmcost = it->cost;
                if(cost == -1 or cost > cmcost){
                    cost = cmcost;
                    center_ptr = it;
                }
            }

            center = center_ptr->point;
            
            auto cmp = close.find(*center_ptr);

            if(cmp == close.end())close.insert(*center_ptr);
            else{
                if(cmp->cost > cost){
                    close.erase(cmp);
                    close.insert(*center_ptr);
                    cost = cmp->cost;
                }
            }

            open.erase(*center_ptr);

            if(euc(center, ptr) <= cell_wide){
                break;
            }

            c_point ops[]={
                c_point{center.x,center.y+cell_wide},
                c_point{center.x,center.y-cell_wide},
                c_point{center.x-cell_wide,center.y},
                c_point{center.x+cell_wide,center.y},
                c_point{center.x-cell_wide,center.y-cell_wide},
                c_point{center.x-cell_wide,center.y+cell_wide},
                c_point{center.x+cell_wide,center.y-cell_wide},
                c_point{center.x+cell_wide,center.y+cell_wide}
            };

            for(int i=0;i<8;i++){
                if(ops[i].x < 0
                    or ops[i].x >= Public::base.w()
                    or ops[i].y < 0
                    or ops[i].y >= Public::base.h()
                    or get_color(ops[i]).b > 250) continue;
                c_point_comp cops = c_point_comp{center, ops[i], get_cost(ops[i], ptr, center)+cost};
                if(close.find(cops) == close.end()){
                    open.insert(cops);
                }
            }

        }

        auto pathmark = close.find({{0,0},center,0});
        if(pathmark == close.end())return -1;

        path.push_back({});
        
        while(!(pathmark->point == pst) ){
            path[path.size()-1].push_back(pathmark->point);
            pathmark = close.find({pathmark->parent,pathmark->parent,0});
        }
        
        path[path.size()-1].push_back(pathmark->point);

        return cost;

    }
}