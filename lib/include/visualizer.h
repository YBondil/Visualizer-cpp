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
        void update();
        void render(bool ShowPoints);
        void clean();
        bool running() { return is_running; };
        void add_object(OBJ_VISU::Object_2D &object);
        void add_segment(OBJ_VISU::Segment &segment);
        void add_point(OBJ_VISU::Point &point);

    private:
        bool is_running;
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::vector<OBJ_VISU::Object_2D> objects;
        std::vector<OBJ_VISU::Point> points;
        std::vector<OBJ_VISU::Segment> segments;
    };

    
}