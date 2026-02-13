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
void Object_2D::rotate(float theta, float center_x, float center_y) {
    for (auto& seg : this->segments) {
        float x1 = seg.get_x1() - center_x;
        float y1 = seg.get_y1() - center_y;
        
        float x1_rot = x1 * std::cos(theta) - y1 * std::sin(theta); 
        float y1_rot = x1 * std::sin(theta) + y1 * std::cos(theta);
        
        float new_x1 = x1_rot + center_x; 
        float new_y1 = y1_rot + center_y;
        
        float x2 = seg.get_x2() - center_x; 
        float y2 = seg.get_y2() - center_y;
        
        float x2_rot = x2 * std::cos(theta) - y2 * std::sin(theta); 
        float y2_rot = x2 * std::sin(theta) + y2 * std::cos(theta);
        
        float new_x2 = x2_rot + center_x; 
        float new_y2 = y2_rot + center_y;
        seg.set(new_x1, new_y1, new_x2, new_y2);
    }
}

void Object_2D::rotate(float theta) {
    this->Object_2D::rotate(theta, center.x, center.y);
}

Triangle_2D::Triangle_2D(float x1,float y1,float x2,float y2,float x3,float y3){
    center.x = (p1.getPosition().x + p2.getPosition().x +p3.getPosition().x)/3 ;
    center.y = (p1.getPosition().y + p2.getPosition().y +p3.getPosition().y)/3 ;
    Segment s1(x1,y1,x2,y2);
    Segment s2(x2,y2,x3,y3 );
    Segment s3(x1,y1,x3,y3);
    this -> add_segment(s1);
    this -> add_segment(s2);
    this -> add_segment(s3);
}



