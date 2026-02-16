#include "visualizer.h"
#include "Obj_visu.h"
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char **argv)
{
    VISU::Visualizer* visualizer = new VISU::Visualizer();
    visualizer->init("Cube 3D", SCREEN_WIDTH, SCREEN_HEIGHT, false);

 
    float size = 100.0f;
    float cx = 400.0f;
    float cy = 300.0f;
    float cz = 0.0f;

    std::vector<OBJ_VISU::Point*> vertices;
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx - size, cy - size, cz - size))); // 0
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx + size, cy - size, cz - size))); // 1
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx + size, cy + size, cz - size))); // 2
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx - size, cy + size, cz - size))); // 3
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx - size, cy - size, cz + size))); // 4
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx + size, cy - size, cz + size))); // 5
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx + size, cy + size, cz + size))); // 6
    vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(cx - size, cy + size, cz + size))); // 7

    OBJ_VISU::Object_3D cube;


    // Face avant
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[0], vertices[1])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[1], vertices[2])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[2], vertices[3])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[3], vertices[0])));
    // Face arrière
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[4], vertices[5])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[5], vertices[6])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[6], vertices[7])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[7], vertices[4])));
    // Arêtes de liaison
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[0], vertices[4])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[1], vertices[5])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[2], vertices[6])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[3], vertices[7])));

    
    visualizer->add_object(&cube);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (visualizer->running())
    {
        frameStart = SDL_GetTicks();

        visualizer->handleEvent();
        
        visualizer->update(); 

        visualizer->render(false); 

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    for(auto* p : vertices) delete p;
    
    visualizer->clean();
    delete visualizer;

    return 0;
}