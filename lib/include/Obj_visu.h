#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "maths.h"


namespace OBJ_VISU {

    class Point {
            friend class Segment ;
            private:

                float x;
                float y;
                SDL_FPoint position;
                SDL_Color color; 

            public:

                Point() : x(0), y(0), position{0, 0}, color{255, 255, 255, 255} {}
                Point(float x, float y) : x(x), y(y), position{x, y}, color({255, 255, 255, 255}) {}
                ~Point() {}
                void init(float new_x, float new_y, SDL_Color col = {255, 255, 255, 255}) {
                    this->x = new_x;
                    this->y = new_y;
                    this->position.x = new_x;
                    this->position.y = new_y;
                    this->color = col ;
                }

                virtual void render(SDL_Renderer* ren) {
                    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
                    SDL_FRect rect = { x - 2, y - 2, 4.0f, 4.0f };
                    SDL_RenderFillRect(ren, &rect);
                }
                SDL_FPoint getPosition() const { return position; }
                void setPosition(float x, float y) {this -> x = x;this -> y = y; position.x = x; position.y = y; } ;
        };

        class Segment {
            private :
                Point* p1 ;
                Point* p2 ;
                SDL_Color color ;

            public :
                Segment(float x1, float y1, float x2, float y2, SDL_Color col) ;
                ~Segment();

                Segment(const Segment& other);
                Segment& operator=(const Segment& other);

                void render (SDL_Renderer* ren, bool ShowPoints);
                void set(float x1, float y1, float x2, float y2);
                float get_x1(){return p1->getPosition().x;}
                float get_y1(){return p1->getPosition().y;}
                float get_x2(){return p1->getPosition().x;}
                float get_y2(){return p1->getPosition().y;}
        };


    class Object_2D {
        private :
            std::vector<Segment> segments ;
        public :
            Object_2D(){};
            ~Object_2D(){};

            void render(SDL_Renderer* ren, bool ShowPoints);
            void add_segment(Segment& segment) ;
            void rotate(float theta);

    };

    class Triangle_2D : public Object_2D {
        private :
            Point p1 ;
            Point p2 ;
            Point p3 ;

        public :
            Triangle_2D(float x1,float y1,float x2,float y2,float x3,float y3);
            ~Triangle_2D(){};
    };
}