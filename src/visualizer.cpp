#include <iostream>
#include "visualizer.h"
using namespace VISU ;

Visualizer::Visualizer(){}
Visualizer::~Visualizer(){}


void Visualizer::init(const char* title, int width, int heigth, bool fullscreen){
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // SDL_Init retourne 0 en cas de succès, sinon une valeur négative (en SDL3)
    if (SDL_Init(SDL_INIT_VIDEO)) { 
        // Utilisez SDL_GetError() pour voir le message précis
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl; 
        is_running = false;
        return;
    }

    window = SDL_CreateWindow(title, width, heigth, flags);
    if (!window) {
        std::cerr << "Window Error: " << SDL_GetError() << std::endl;
        is_running = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Renderer Error: " << SDL_GetError() << std::endl;
        is_running = false;
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        is_running = true;
    }

}

void Visualizer::handleEvent(){
    SDL_Event event ;
    SDL_PollEvent(&event) ;
    switch(event.type){
        case SDL_EVENT_QUIT :
            is_running = false ;
            break ;
        default :
            break ;
    }
}

void Visualizer::update(){

}

void Visualizer::render(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Visualizer::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}