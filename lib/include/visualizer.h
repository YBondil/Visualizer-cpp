#pragma once 
#include <SDL3/SDL.h>
#include "maths.h"

namespace VISU{
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

        private :
            bool is_running ;
            SDL_Window * window ;
            SDL_Renderer* renderer ;


    };

    class Object{

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