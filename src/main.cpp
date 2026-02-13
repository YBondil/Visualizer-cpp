#include "visualizer.h"
#include "Obj_visu.h"
#define WHITE {255,255,255,255}
#define SHOWPOINTS false

VISU::Visualizer* visualizer;


int main(int argc, char **argv) {

    OBJ_VISU::Triangle_2D triangle(100.f,100.f,100.f,200.f,200.f,200.f) ;

    
    visualizer = new VISU::Visualizer;


    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime ;

    visualizer->init("Visualizer", 800, 600, false); 
    visualizer->add_object(triangle);


    while (visualizer->running()) {
        frameStart = SDL_GetTicks();

        visualizer->handleEvent();
        visualizer->update();
        visualizer->render(SHOWPOINTS);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    visualizer->clean();
    delete visualizer;
    
    return 0;
}