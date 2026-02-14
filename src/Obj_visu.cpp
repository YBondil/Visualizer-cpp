#include "Obj_visu.h"
#include <fstream>
#include <cmath>


BASICS::Segment::Segment(Float3 pos1, Float3 pos2, SDL_Color col = {255, 255, 255, 255})
{
    this->p1 = new Point;
    this->p2 = new Point;
    p1->init(pos1, col);
    p2->init(pos2, col);
    this->color = col;
}

BASICS::Segment::~Segment()
{
    delete p1;
    delete p2;
}
BASICS::Segment::Segment(const Segment &other)
{
    this->p1 = new Point();
    this->p2 = new Point();
    *this->p1 = *other.p1;
    *this->p2 = *other.p2;

    this->color = other.color;
}
BASICS::Segment &BASICS::Segment::operator=(const Segment &other)
{
    if (this == &other)
    {
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

void BASICS::Segment::render(SDL_Renderer *ren, bool ShowPoints)
{
    if (ShowPoints)
    {
        p1->render(ren);
        p2->render(ren);
    }
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    SDL_FPoint points[] = {p1->positionOnScreen, p2->positionOnScreen};
    SDL_RenderLines(ren, points, 2);
}
void BASICS::Segment::set(Float3 pos1, Float3 pos2)
{
    this->p1->init(pos1);
    this->p2->init(pos2);
}



void OBJ_VISU_2D::Object::add_segment(BASICS::Segment &segment)
{
    this->segments.push_back(segment);
}
void OBJ_VISU_2D::Object::render(SDL_Renderer *ren, bool ShowPoints)
{
    for (auto &segment : this->segments)
    {
        segment.render(ren, ShowPoints);
    }
}
void OBJ_VISU_2D::Object::rotate(float theta, float center_x, float center_y)
{
    for (auto &seg : this->segments)
    {
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
    this->updateCenter();
}

void Object_2D::rotate(float theta)
{
    this->Object_2D::rotate(theta, center.x, center.y);
}

Triangle_2D::Triangle_2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float cx = (x1 + x2 + x3) / 3.0f;
    float cy = (y1 + y2 + y3) / 3.0f;

    center.setPosition(cx, cy);

    Segment s1(x1, y1, x2, y2);
    Segment s2(x2, y2, x3, y3);
    Segment s3(x1, y1, x3, y3);

    this->add_segment(s1);
    this->add_segment(s2);
    this->add_segment(s3);

    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    p3.x = x3;
    p3.y = y3;
}

void Object_2D::updateCenter()
{
    float mid_x = 0;
    float mid_y = 0;

    for (auto &segment : segments)
    {
        mid_x += (segment.get_x1() + segment.get_x2()) / 2;
        mid_y += (segment.get_y1() + segment.get_y2()) / 2;
    }
    if (!segments.empty())
    {
        center.x = mid_x / static_cast<float>(segments.size());
        center.y = mid_y / static_cast<float>(segments.size());
    }
}
