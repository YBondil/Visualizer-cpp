#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <cmath>

class Camera;

namespace OBJ_VISU
{

    struct Float3
    {
        float x, y, z;
        Float3() : x(0), y(0), z(0) {}
        Float3(float a, float b, float c) : x(a), y(b), z(c) {}

        Float3 operator+(const Float3 &other) const;
        Float3 operator-(const Float3 &other) const;
        Float3 operator*(float lambda) const;
        float distanceCarre(const Float3 &b) const;
        Float3 crossProduct(const Float3 &other) const;
        float dotProduct(const Float3 &other) const;
        void normalize();
    };

    class Object
    {
    public:
        Object() {}
        virtual ~Object() {}

        virtual void render(SDL_Renderer *ren, Camera *cam, bool ShowPoints) = 0;
        virtual void rotate(float theta_x, float theta_y, float theta_z) {}
        virtual void project(Camera *cam) = 0;
    };

    class Point : public Object
    {
        friend class Segment;
        friend class Object_2D;
        friend class Triangle_2D;
        friend class Object_3D;
        friend class Face;

    private:
        Float3 coords;
        SDL_FPoint positionOnScreen;
        SDL_Color color;

    public:
        Point() : coords(), positionOnScreen{0, 0}, color{255, 255, 255, 255} {}
        Point(Float3 pos) : coords(pos), positionOnScreen{0, 0}, color{255, 255, 255, 255} {}
        virtual ~Point() {}

        void init(Float3 new_pos, SDL_Color col = {255, 255, 255, 255})
        {
            this->coords = new_pos;
            this->color = col;
        }

        virtual void render(SDL_Renderer *ren, Camera *cam, bool ShowPoint) override
        {
            if (!ShowPoint)
                return;
            SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            SDL_FRect rect = {positionOnScreen.x - 1, positionOnScreen.y - 1, 2.0f, 2.0f};
            SDL_RenderFillRect(ren, &rect);
        }

        Float3 getPosition() const { return coords; }
        Float3 &getPositionRef() { return coords; }

        void setPositionOnScreen(float x, float y)
        {
            positionOnScreen.x = x;
            positionOnScreen.y = y;
        }
        virtual void project(Camera *cam) override;
        void rotate(float theta_x, float theta_y, float theta_z, Float3 center);
    };

    class Segment : public Object
    {
    private:
        Point *p1;
        Point *p2;
        SDL_Color color;
        bool owns_points;

    public:
        Segment(Float3 pos1, Float3 pos2, SDL_Color col = {255, 255, 255, 255});
        Segment(Point *ptr1, Point *ptr2, SDL_Color col = {255, 255, 255, 255});

        virtual ~Segment();

        Segment(const Segment &other);
        Segment &operator=(const Segment &other);

        virtual void render(SDL_Renderer *ren, Camera *cam, bool ShowPoints) override;
        virtual void project(Camera *cam) override;

        void set(Float3 pos1, Float3 pos2);

        Point *getP1() { return p1; };
        Point *getP2() { return p2; };
    };

    class Object_2D : public Object
    {
    protected:
        std::vector<Segment> segments;
        Point center;

    public:
        Object_2D() {}
        virtual ~Object_2D() {}

        virtual void render(SDL_Renderer *ren, Camera *cam, bool ShowPoints) override;
        void add_segment(Segment &segment);

        void rotate(float theta);
        virtual void rotate(float theta, float center_x, float center_y) override;

        void updateCenter();
        virtual void project(Camera *cam) override;
    };

    class Triangle_2D : public Object_2D
    {
    private:
        Float3 p1_coords, p2_coords, p3_coords;

    public:
        Triangle_2D(float x1, float y1, float x2, float y2, float x3, float y3);
        ~Triangle_2D() {}
    };
    class Face : public Object
    {
    private:
        Point *p1;
        Point *p2;
        Point *p3;
        SDL_Color color;

    public:
        Face(Point *ptr1, Point *ptr2, Point *ptr3, SDL_Color col)
            : p1(ptr1), p2(ptr2), p3(ptr3), color(col) {}

        virtual ~Face() {}

        float getCameraDistance(Camera *cam) const;

        virtual void project(Camera *cam) override
        {
            p1->project(cam);
            p2->project(cam);
            p3->project(cam);
        }

        virtual void render(SDL_Renderer *ren, Camera *camera, bool ShowPoints) override;
        void rotate(float theta_x, float theta_y, float theta_z, Float3 center);
    };

    class Object_3D : public Object
    {
    private:
        std::vector<Segment> segments;
        std::vector<Face> faces;
        std::vector<Point *> vertices;
        Float3 center;

    public:
        Object_3D() {}
        virtual ~Object_3D() {}

        virtual void render(SDL_Renderer *ren, Camera *cam, bool ShowPoints) override;
        void add_segment(Segment &segment);
        void add_face(Face face);
        void add_point(Point *p) { vertices.push_back(p); }

        virtual void rotate(float theta_x, float theta_y, float theta_z) override;
        void rotateArround(float theta_x, float theta_y, float theta_z, Float3 point);
        void updateCenter();
        virtual void project(Camera *cam) override;
        
    };
    Object_3D* create_subdivided_floor(float size, float y_pos, int subdivisions, SDL_Color color);
}
