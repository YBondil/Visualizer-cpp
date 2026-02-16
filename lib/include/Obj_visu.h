#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <cmath>
#include "maths.h"

namespace OBJ_VISU {

    struct Float3 {
        float x;
        float y;
        float z;
        Float3() { x = 0; y = 0; z = 0; };
        Float3(float a, float b, float c) { x = a; y = b; z = c; };
        Float3 operator+(Float3& other){Float3 res; res.x = this->x + other.x;res.y = this->y + other.y;res.z = this->z + other.z;return res;}
    };

    class Point
    {
        friend class Segment;
        friend class Object_2D;
        friend class Triangle_2D;
        friend class Object_3D;

    private:
        Float3 coords;
        SDL_FPoint positionOnScreen;
        SDL_Color color;

    public:
        Point() : coords(Float3()), positionOnScreen{ 0, 0 }, color{ 255, 255, 255, 255 } {}
        Point(Float3 pos) : coords(pos), positionOnScreen{ 0,0 }, color({ 255, 255, 255, 255 }) {};
        ~Point() {}
        
        void init(Float3 new_pos, SDL_Color col = { 255, 255, 255, 255 })
        {
            this->coords = new_pos;
            this->color = col;
        }

        virtual void render(SDL_Renderer* ren)
        {
            SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            SDL_FRect rect = { positionOnScreen.x - 1, positionOnScreen.y - 1, 2.0f, 2.0f };
            SDL_RenderFillRect(ren, &rect);
        }

        Float3 getPosition() { return coords; };
        
        void setPositionOnScreen(float x, float y)
        {
            positionOnScreen.x = x;
            positionOnScreen.y = y;
        };
    };

    class Segment
    {
    private:
        Point* p1;
        Point* p2;
        SDL_Color color;

    public:
        Segment(Float3 p1, Float3 p2, SDL_Color col = { 255, 255, 255, 255 });
        ~Segment();

        Segment(const Segment& other);
        Segment& operator=(const Segment& other);

        void render(SDL_Renderer* ren, bool ShowPoints);
        void set(Float3 pos1, Float3 pos2);
        
        float get_x1() { return p1->getPosition().x; }
        float get_y1() { return p1->getPosition().y; }
        float get_x2() { return p2->getPosition().x; }
        float get_y2() { return p2->getPosition().y; }

        Point* getP1() { return p1; }
        Point* getP2() { return p2; }
    };

    class Object_2D
    {
        friend class Triangle_2D;

    protected: 
        std::vector<Segment> segments;
        Point center;

    public:
        Object_2D() {};
        virtual ~Object_2D() {};

        void render(SDL_Renderer* ren, bool ShowPoints);
        void add_segment(Segment& segment);
        
        void rotate(float theta, float center_x, float center_y);
        void rotate(float theta);
        
        void updateCenter();
    };

    class Triangle_2D : public Object_2D
    {
    private:
        Float3 p1_coords, p2_coords, p3_coords;

    public:
        Triangle_2D(float x1, float y1, float x2, float y2, float x3, float y3);
        ~Triangle_2D() {};
    };

    class Object_3D
    {
    private:
        std::vector<Segment> segments;
        Float3 center;

    public:
        Object_3D() {};
        ~Object_3D() {};

        void render(SDL_Renderer* ren, bool ShowPoints);
        void add_segment(Segment& segment);
        
        void rotate(float theta_x, float theta_y, float theta_z);
        
        void updateCenter();
    };

    class Triangle_3D : public Object_3D
    {
    private:
        Float3 p1_coords, p2_coords, p3_coords;

    public:
        Triangle_3D();
        ~Triangle_3D() {};
    };
}