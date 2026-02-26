#include "visualizer.h"
#include "Obj_visu.h"
#include "read_file.h"
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
    visualizer->init("Moteur 3D - Chargement STL", SCREEN_WIDTH, SCREEN_HEIGHT, false);

    // --- CHARGEMENT DU FICHIER STL ---
    SDL_Color modelColor = { 200, 200, 200, 255 }; // Gris clair
    
    // Remplacez "mon_modele.stl" par le chemin vers votre vrai fichier .stl
    OBJ_VISU::Object_3D* stl_model = VISU::load_stl("model/teapot.stl", modelColor); 
    OBJ_VISU::Object_3D* sol = OBJ_VISU::create_subdivided_floor(800.0f, 200.0f, 100, GRAY);
    
    if (stl_model != nullptr) {
        visualizer->add_object(stl_model);
    }
    if (sol != nullptr){
        visualizer->add_object(sol);
    }


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


    
    visualizer->clean();
    delete visualizer;

    return 0;
}