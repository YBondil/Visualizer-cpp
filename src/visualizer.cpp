#include "visualizer.h"
#include <iostream>

Visualizer::Visualizer(){}
Visualizer::~Visualizer(){}

void Visualizer::init(const char* title, int width, int heigth, bool fullscreen){
    int flags = 0 ;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN ;
    }
    if (SDL_Init(SDL_INIT_VIDEO) == 0){
        window = SDL_CreateWindow(title, width, heigth, flags) ;
        if (window){
            std::cout << "Window initialized" << std::endl ; 
        }
        renderer = SDL_CreateRenderer(window, NULL) ;
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 255,255,255,255) ;
            std::cout << "Renderer initialized" << std::endl ;
        }
        is_running = true ;
    } else {
        is_running = false;

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