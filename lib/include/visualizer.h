#pragma once 
#include <SDL3/SDL.h>
#include <vector>
#include "maths.h"

namespace VISU{

    class Object{
        private :
            int x ;
            int y ;
            SDL_FPoint segment;

        public :
            Object(){} ;
            Object(int x, int y){x = x; y = y ; segment.x = x; segment.y = y ;};
            ~Object(){};

            void render(SDL_Renderer* ren){
                SDL_SetRenderDrawColor(ren, 255,255,255,255);
                SDL_RenderLines(ren,&segment,1);
                SDL_SetRenderDrawColor(ren, 0,0,0,255);};
                

            void init(int x, int y){x = x; y = y ; segment.x = x; segment.y = y ;};
    };

    class Visualizer {

        public :
            Visualizer();
            ~Visualizer(); 

            void init(const char* title,int width, int heigth, bool fullscreen) ;
            void handleEvent() ;
            void update();
            void render();
            void clean();
            bool running(){return is_running;};
            void add_object(Object& object);

        private :
            bool is_running ;
            SDL_Window * window ;
            SDL_Renderer* renderer ;
            std::vector<Object> objects;


    };

    
    class Camera {
        private :

            MATHS::N3 position ;
            int yaw = 0;
            int pitch = 0 ;
            int fov ;

        public :
            Camera(int fov);
            ~Camera();

            void rotate(int delta_yaw, int delta_pitch) ; 
            void move(MATHS::N3 delta_position) ;
            MATHS::N3 get_position() const {return position ;}

        

    };
}