#include "Obj_visu.h"
#include <fstream>
using namespace OBJ_VISU ;

Segment::Segment(float x1, float x2, float y1, float y2, SDL_Color col = {255, 255, 255, 255}){
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


Object_2D::Object_2D(){
    
}
