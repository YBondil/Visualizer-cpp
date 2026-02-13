#include "visualizer.h"
#include "Obj_visu.h"
#define WHITE {255,255,255,255}
#define SHOWPOINTS false

VISU::Visualizer* visualizer;

int main(int argc, char **argv) {

    visualizer = new VISU::Visualizer;
    visualizer->init("Visualizer", 800, 600, false); 

    OBJ_VISU::Segment segm1(100.0f,100.0f,300.0f,500.0f, WHITE);

    
    visualizer->add_segment(segm1);

    while (visualizer->running()) {
        visualizer->handleEvent();
        visualizer->update();
        visualizer->render(SHOWPOINTS);
    }

    visualizer->clean();
    delete visualizer;
    
    return 0;
}