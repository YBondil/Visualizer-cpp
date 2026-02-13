#include <iostream>
#include "visualizer.h"
using namespace VISU ;

Segment::Segment(float x1, float x2, float y1, float y2, SDL_Color col = {255, 255, 255, 255}){
    this -> p1 = new Point;
    this -> p2 = new Point;
    p1 -> init(x1, y1, col);
    p2 -> init(x2, y2, col);
    this -> color = col ;
    
}

Segment::~Segment(){
    delete p1 ;
    delete p2 ;
}




Visualizer::Visualizer(){}
Visualizer::~Visualizer(){}


void Visualizer::init(const char* title, int width, int heigth, bool fullscreen){
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // SDL_Init retourne 0 en cas de succès, sinon une valeur négative (en SDL3)
    if (!SDL_Init(SDL_INIT_VIDEO)) { 
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

}

void Visualizer::render(){
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    for (auto& object : points){
        object.render(renderer);
    }
    for (auto& segment : segments){
        segment.render(renderer);
    }
    SDL_RenderPresent(renderer);
}

void Visualizer::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Visualizer::add_point(Point& point){
    points.push_back(point);
}
void Visualizer::add_segment(Segment& segment){
    segments.push_back(segment);
}