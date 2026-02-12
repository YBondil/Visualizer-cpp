#pragma once 
#include <SDL3/SDL.h>

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