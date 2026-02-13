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
    if (!SDL_Init(SDL_INIT_VIDEO)) { 
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        is_running = true;
    }

}

void Visualizer::handleEvent(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_EVENT_QUIT :
                is_running = false;
                break;
        }
    }
}

void Visualizer::update(){
    for (auto& object : objects){
        object.rotate(0.2f);
    }
}

void Visualizer::render(bool ShowPoints = false){
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    
    for (auto& object : this -> objects){
        object.render(renderer, ShowPoints);
    }
    SDL_RenderPresent(renderer);
}

void Visualizer::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Visualizer::add_object(OBJ_VISU::Object_2D& object){
    objects.push_back(object);
}