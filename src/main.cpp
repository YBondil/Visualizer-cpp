#include "visualizer.h"
#include "Obj_visu.h"
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Color RED = {255, 0, 0, 255};
SDL_Color GREEN = {0, 255, 0, 255};
SDL_Color BLUE = {0, 0, 255, 255};
SDL_Color YELLOW = {255, 255, 0, 255};
SDL_Color CYAN = {0, 255, 255, 255};
SDL_Color MAGENTA = {255, 0, 255, 255};
int main(int argc, char **argv)
{
    VISU::Visualizer* visualizer = new VISU::Visualizer();
    visualizer->init("Cube 3D", SCREEN_WIDTH, SCREEN_HEIGHT, false);

 
    float size = 100.0f;
    float cx = 0.0f;
    float cy = 0.0f;
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
    // Face Avant (Z-size) -> Points 0, 1, 2, 3
    // Triangle 1 (0-1-2)
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[1], vertices[2], RED));
    // Triangle 2 (0-2-3)
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[2], vertices[3], RED));

    // Face Arrière (Z+size) -> Points 4, 5, 6, 7
    cube.add_face(OBJ_VISU::Face(vertices[4], vertices[5], vertices[6], GREEN));
    cube.add_face(OBJ_VISU::Face(vertices[4], vertices[6], vertices[7], GREEN));

    // Face Droite (X+size) -> Points 1, 5, 6, 2
    cube.add_face(OBJ_VISU::Face(vertices[1], vertices[5], vertices[6], BLUE));
    cube.add_face(OBJ_VISU::Face(vertices[1], vertices[6], vertices[2], BLUE));

    // Face Gauche (X-size) -> Points 0, 4, 7, 3
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[4], vertices[7], YELLOW));
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[7], vertices[3], YELLOW));

    // Face Haut (Y-size) -> Points 3, 2, 6, 7 (Attention au sens Y dans votre repère)
    cube.add_face(OBJ_VISU::Face(vertices[3], vertices[2], vertices[6], CYAN));
    cube.add_face(OBJ_VISU::Face(vertices[3], vertices[6], vertices[7], CYAN));

    // Face Bas (Y+size) -> Points 0, 1, 5, 4
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[1], vertices[5], MAGENTA));
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[5], vertices[4], MAGENTA));
    
    for(auto* p : vertices) {
        cube.add_point(p); 
    }

    visualizer->add_object(&cube);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    int count;

    while (visualizer->running())
    {   
        count ++;
        frameStart = SDL_GetTicks();

        visualizer->handleEvent();
        
        visualizer->update(count); 

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