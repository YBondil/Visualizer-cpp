#include "Obj_visu.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace OBJ_VISU;

Segment::Segment(Float3 pos1, Float3 pos2, SDL_Color col) : owns_points(true)
{
    this->p1 = new Point;
    this->p2 = new Point;
    p1->init(pos1, col);
    p2->init(pos2, col);

    p1->setPositionOnScreen(0, 0); 
    p2->setPositionOnScreen(0, 0);
    this->color = col;
}

Segment::Segment(Point* ptr1, Point* ptr2, SDL_Color col) 
    : p1(ptr1), p2(ptr2), color(col), owns_points(false)
{
}

Segment::~Segment()
{
    if (owns_points) {
        delete p1;
        delete p2;
    }
}

Segment::Segment(const Segment& other) : owns_points(true)
{
    this->p1 = new Point();
    this->p2 = new Point();
    *this->p1 = *other.p1;
    *this->p2 = *other.p2;
    this->color = other.color;
}

Segment& Segment::operator=(const Segment& other)
{
    if (this == &other) return *this;

    if (owns_points) {
        delete p1;
        delete p2;
    }

    owns_points = true;
    p1 = new Point();
    p2 = new Point();

    *p1 = *other.p1;
    *p2 = *other.p2;
    this->color = other.color;
    return *this;
}

void Segment::render(SDL_Renderer* ren, bool ShowPoints)
{
    if (ShowPoints)
    {
        p1->render(ren,true);
        p2->render(ren,true);
    }
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    SDL_RenderLine(ren, 
        p1->positionOnScreen.x, p1->positionOnScreen.y, 
        p2->positionOnScreen.x, p2->positionOnScreen.y
    );
}

void Segment::set(Float3 pos1, Float3 pos2)
{
    this->p1->init(pos1);
    this->p2->init(pos2);
}


void Object_2D::add_segment(Segment& segment)
{
    this->segments.push_back(segment);
    updateCenter(); 
}

void Object_2D::render(SDL_Renderer* ren, bool ShowPoints)
{
    for (auto& segment : this->segments)
    {
        segment.render(ren, ShowPoints);
    }
}
void Object_2D::rotate(float theta_x, float theta_y, float theta_z) {
        this->rotate(theta_z);
    }
void Object_2D::rotate(float theta, float center_x, float center_y)
{
    for (auto& seg : this->segments)
    {

        float x1 = seg.getP1()->coords.x - center_x;
        float y1 = seg.getP1()->coords.y - center_y;

        float x1_rot = x1 * std::cos(theta) - y1 * std::sin(theta);
        float y1_rot = x1 * std::sin(theta) + y1 * std::cos(theta);

        Float3 new_p1(x1_rot + center_x, y1_rot + center_y, 0);

        float x2 = seg.getP2()->coords.x - center_x;
        float y2 = seg.getP2()->coords.y - center_y;

        float x2_rot = x2 * std::cos(theta) - y2 * std::sin(theta);
        float y2_rot = x2 * std::sin(theta) + y2 * std::cos(theta);

        Float3 new_p2(x2_rot + center_x, y2_rot + center_y, 0);

        seg.set(new_p1, new_p2);
    }
    this->updateCenter();
}

void Object_2D::rotate(float theta)
{
    this->rotate(theta, center.getPosition().x, center.getPosition().y);
}

void Object_2D::updateCenter()
{
    float mid_x = 0;
    float mid_y = 0;

    if (segments.empty()) return;

    for (auto& segment : segments)
    {
        mid_x += (segment.getP1()->coords.x + segment.getP2()->coords.x) / 2;
        mid_y += (segment.getP1()->coords.y + segment.getP2()->coords.y) / 2;
    }
    
    float cx = mid_x / static_cast<float>(segments.size());
    float cy = mid_y / static_cast<float>(segments.size());
    
    center.init(Float3(cx, cy, 0));
}



Triangle_2D::Triangle_2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
    p1_coords = {x1, y1, 0};
    p2_coords = {x2, y2, 0};
    p3_coords = {x3, y3, 0};

    Segment s1(p1_coords, p2_coords);
    Segment s2(p2_coords, p3_coords);
    Segment s3(p3_coords, p1_coords); 

    this->add_segment(s1);
    this->add_segment(s2);
    this->add_segment(s3);

    this->updateCenter();
}

// ==========================================
// Implementation OBJECT_3D
// ==========================================

void Object_3D::add_segment(Segment& segment)
{
    this->segments.push_back(segment);
    updateCenter();
}

void Object_3D::render(SDL_Renderer* ren, bool ShowPoints)
{
    for (auto& segment : this->segments)
    {
        segment.render(ren, ShowPoints);
    }
}

void Object_3D::rotate(float theta_x, float theta_y, float theta_z)
{
    float cx = center.x;
    float cy = center.y;
    float cz = center.z;

    for (auto& seg : this->segments)
    {
        Point* points[] = { seg.getP1(), seg.getP2() };

        for (auto* p : points) {
            // Note: Si les points sont partagés entre plusieurs segments,
            // cette approche naïve va faire tourner le même point plusieurs fois par frame.
            // Pour l'instant, cela fonctionne car tes segments 3D actuels ne partagent pas d'instance de Point.
            
            float x = p->getPosition().x - cx;
            float y = p->getPosition().y - cy;
            float z = p->getPosition().z - cz;
            
            // Rotation Z
            if (theta_z != 0) {
                float old_x = x; 
                x = x * cos(theta_z) - y * sin(theta_z);
                y = old_x * sin(theta_z) + y * cos(theta_z);
            }

            // Rotation Y
            if (theta_y != 0) {
                float old_x = x;
                x = x * cos(theta_y) + z * sin(theta_y);
                z = -old_x * sin(theta_y) + z * cos(theta_y);
            }
            
            // Rotation X
            if (theta_x != 0) {
                float old_y = y;
                y = y * cos(theta_x) - z * sin(theta_x);
                z = old_y * sin(theta_x) + z * cos(theta_x);
            }

            p->init(Float3(x + cx, y + cy, z + cz));
        }
    }
}

void Object_3D::updateCenter()
{
    float mid_x = 0;
    float mid_y = 0;
    float mid_z = 0;

    if (segments.empty()) return;

    for (auto& segment : segments)
    {
        mid_x += (segment.getP1()->getPosition().x + segment.getP2()->getPosition().x) / 2;
        mid_y += (segment.getP1()->getPosition().y + segment.getP2()->getPosition().y) / 2;
        mid_z += (segment.getP1()->getPosition().z + segment.getP2()->getPosition().z) / 2;
    }

    center.x = mid_x / static_cast<float>(segments.size());
    center.y = mid_y / static_cast<float>(segments.size());
    center.z = mid_z / static_cast<float>(segments.size());
}