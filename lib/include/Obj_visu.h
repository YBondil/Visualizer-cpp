#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "maths.h"
#include "camera.h"

namespace BASICS{
struct Float3 {
    float x;
    float y;
    float z;
    Float3(){x = 0; y = 0; z=0;};
    Float3(float a, float b, float c){x = a; y = b; z=c;};
};

class Point
{
    friend class Segment;
    friend class Object_2D;
    friend class Triangle_2D;

private:
    Float3 coords ; 
    SDL_FPoint positionOnScreen;
    SDL_Color color;
    

public:
    Point() : coords( Float3() ), positionOnScreen{0, 0}, color{255, 255, 255, 255} {}
    Point(Float3 pos) : coords (pos), positionOnScreen{0,0}, color({255, 255, 255, 255}) {};
    ~Point() {}
    void init(Float3 new_pos, SDL_Color col = {255, 255, 255, 255})
    {
        this->coords = new_pos ;
        this->color = col;
    }

    virtual void render(SDL_Renderer *ren)
    {
        SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
        SDL_FRect rect = {positionOnScreen.x - 1, positionOnScreen.x - 1, 2.0f, 2.0f};
        SDL_RenderFillRect(ren, &rect);
    }

    Float3 getPosition(){return coords ;};

    void setPositionOnScreen(float x, float y)
    {
        positionOnScreen.x = x ;
        positionOnScreen.y = y ;
    };
};


class Segment
{
private:
    Point *p1;
    Point *p2;
    SDL_Color color;

public:
    Segment(Float3 p1, Float3 p2, SDL_Color col);
    ~Segment();

    Segment(const Segment &other);
    Segment &operator=(const Segment &other);

    void render(SDL_Renderer *ren, bool ShowPoints);
    void set(Float3 pos1, Float3 pos2);
    float get_x1() { return p1->getPosition().x; }
    float get_y1() { return p1->getPosition().y; }
    float get_x2() { return p2->getPosition().x; }
    float get_y2() { return p2->getPosition().y; }
};
}


namespace OBJ_VISU_2D
{
    class Object
    {
        friend class Triangle_2D;

    private:
        std::vector<BASICS::Segment> segments;
        BASICS::Point center;

    public:
        Object() {};
        ~Object() {};

        void render(SDL_Renderer *ren, bool ShowPoints);
        void add_segment(BASICS::Segment &segment);
        void rotate(float theta, float center_x, float center_y);
        void rotate(float theta);
        void updateCenter();
    };

    class Triangle_2D : public Object_2D
    {
    private:
        Point p1;
        Point p2;
        Point p3;

    public:
        Triangle_2D(float x1, float y1, float x2, float y2, float x3, float y3);
        ~Triangle_2D() {};
    };
}

namespace OBJ_VISU_3D
{

    class Object
    {
    private:
        std::vector<OBJ_VISU_2D::Segment> segments;
        OBJ_VISU_2D center;

    public:
        Object() {};
        ~Object() {};

        void render(SDL_Renderer *ren, bool ShowPoints);
        void add_segment(Segment &segment);
        void rotate(float theta, float center_x, float center_y);
        void rotate(float theta);
        void updateCenter();
    };
};
}