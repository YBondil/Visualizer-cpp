#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Obj_visu.h"

namespace VISU
{

    class Visualizer
    {

    public:
        Visualizer();
        ~Visualizer();

        void init(const char *title, int width, int heigth, bool fullscreen);
        void handleEvent();
        void update(int count);
        void render(bool ShowPoints);
        void clean();
        bool running() { return is_running; };
        void add_object(OBJ_VISU::Object* object);

    private:
        bool is_running;
        Camera* camera;
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::vector<OBJ_VISU::Object*> objects;
    };

    
}