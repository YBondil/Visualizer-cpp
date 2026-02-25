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
SDL_Color GRAY = {128, 128, 128, 255}; // Couleur pour le sol

int main(int argc, char **argv)
{
    VISU::Visualizer* visualizer = new VISU::Visualizer();
    visualizer->init("Cube 3D et Sol", SCREEN_WIDTH, SCREEN_HEIGHT, false);

    float size = 100.0f;
    float cx = 0.0f;
    float cy = 0.0f;
    float cz = 0.0f;

    // --- CRÉATION DU CUBE ---
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

    cube.add_segment(*(new OBJ_VISU::Segment(vertices[0], vertices[1])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[1], vertices[2])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[2], vertices[3])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[3], vertices[0])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[4], vertices[5])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[5], vertices[6])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[6], vertices[7])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[7], vertices[4])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[0], vertices[4])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[1], vertices[5])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[2], vertices[6])));
    cube.add_segment(*(new OBJ_VISU::Segment(vertices[3], vertices[7])));

    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[1], vertices[2], RED));
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[2], vertices[3], RED));
    cube.add_face(OBJ_VISU::Face(vertices[4], vertices[5], vertices[6], GREEN));
    cube.add_face(OBJ_VISU::Face(vertices[4], vertices[6], vertices[7], GREEN));
    cube.add_face(OBJ_VISU::Face(vertices[1], vertices[5], vertices[6], BLUE));
    cube.add_face(OBJ_VISU::Face(vertices[1], vertices[6], vertices[2], BLUE));
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[4], vertices[7], YELLOW));
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[7], vertices[3], YELLOW));
    cube.add_face(OBJ_VISU::Face(vertices[3], vertices[2], vertices[6], CYAN));
    cube.add_face(OBJ_VISU::Face(vertices[3], vertices[6], vertices[7], CYAN));
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[1], vertices[5], MAGENTA));
    cube.add_face(OBJ_VISU::Face(vertices[0], vertices[5], vertices[4], MAGENTA));
    
    for(auto* p : vertices) {
        cube.add_point(p); 
    }
    visualizer->add_object(&cube);

    // --- CRÉATION DU SOL ---
    float floor_y = 200.0f; // Positionné en dessous du cube (axe Y vers le bas)
    float floor_size = 800.0f; // Un grand plan
    
    std::vector<OBJ_VISU::Point*> floor_vertices;
    floor_vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(-floor_size, floor_y, -floor_size))); // 0
    floor_vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(floor_size, floor_y, -floor_size)));  // 1
    floor_vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(floor_size, floor_y, floor_size)));   // 2
    floor_vertices.push_back(new OBJ_VISU::Point(OBJ_VISU::Float3(-floor_size, floor_y, floor_size)));  // 3

    OBJ_VISU::Object_3D sol;

    // Définition des contours du sol
    sol.add_segment(*(new OBJ_VISU::Segment(floor_vertices[0], floor_vertices[1])));
    sol.add_segment(*(new OBJ_VISU::Segment(floor_vertices[1], floor_vertices[2])));
    sol.add_segment(*(new OBJ_VISU::Segment(floor_vertices[2], floor_vertices[3])));
    sol.add_segment(*(new OBJ_VISU::Segment(floor_vertices[3], floor_vertices[0])));

    // Remplissage du sol (2 triangles)
    sol.add_face(OBJ_VISU::Face(floor_vertices[0], floor_vertices[1], floor_vertices[2], GRAY));
    sol.add_face(OBJ_VISU::Face(floor_vertices[0], floor_vertices[2], floor_vertices[3], GRAY));

    for(auto* p : floor_vertices) {
        sol.add_point(p); 
    }
    visualizer->add_object(&sol);


    // --- BOUCLE PRINCIPALE ---
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    int count = 0;

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

    // Libération de la mémoire
    for(auto* p : vertices) delete p;
    for(auto* p : floor_vertices) delete p;
    
    visualizer->clean();
    delete visualizer;

    return 0;
}