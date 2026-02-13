#include "Obj_visu.h"
#include <fstream>
#include <cmath>
using namespace OBJ_VISU ;

Segment::Segment(float x1, float y1, float x2, float y2, SDL_Color col = {255, 255, 255, 255}){
    this -> p1 = new Point;
    this -> p2 = new Point;
    p1 -> init(x1, y1, col);
    p2 -> init(x2, y2, col);
    this -> color = col ;
    
}

Segment::~Segment(){
    delete p1 ;
    delete p2 ;
}
Segment::Segment(const Segment& other) {
    this->p1 = new Point();
    this->p2 = new Point();
    *this->p1 = *other.p1; 
    *this->p2 = *other.p2;
    
    this->color = other.color;
}
Segment& Segment::operator=(const Segment& other) {
    if (this == &other) {
        return *this;
    }
    delete p1;
    delete p2;

    p1 = new Point();
    p2 = new Point();
    
    *p1 = *other.p1;
    *p2 = *other.p2;
    color = other.color;
    return *this;
}

void Segment::render (SDL_Renderer* ren, bool ShowPoints) {
    if (ShowPoints){
        p1->render(ren);
        p2->render(ren);
    }
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    SDL_FPoint points [] = {p1->position,p2->position};
    SDL_RenderLines(ren, points ,2); 
}
void Segment::set(float x1, float y1, float x2, float y2){
    this -> p1 -> setPosition(x1,y1) ;
    this -> p2 -> setPosition(x2,y2) ;
}


void Object_2D::add_segment(Segment& segment){
    this->segments.push_back(segment) ;
}
void Object_2D::render(SDL_Renderer* ren, bool ShowPoints){
    for (auto& segment : this -> segments){
        segment.render(ren,ShowPoints);
    }
}

void Object_2D::rotate(float theta){
    for (auto& seg : this -> segments){
        float x1_bis = seg.get_x1()*std::cos(theta) - seg.get_y1()*std::sin(theta);
        float y1_bis = seg.get_x1()*std::sin(theta) + seg.get_y1()*std::cos(theta);

        float x2_bis = seg.get_x1()*std::cos(theta) - seg.get_y1()*std::sin(theta);
        float y2_bis = seg.get_x1()*std::sin(theta) + seg.get_y1()*std::cos(theta);
        
        seg.set(x1_bis,y1_bis,x2_bis, y2_bis) ;
    }
}

Triangle_2D::Triangle_2D(float x1,float y1,float x2,float y2,float x3,float y3){
    Segment s1(x1,y1,x2,y2);
    Segment s2(x2,y2,x3,y3 );
    Segment s3(x1,y1,x3,y3);
    this -> add_segment(s1);
    this -> add_segment(s2);
    this -> add_segment(s3);
}

