#include "visualizer.h"



Visualizer * visualizer ;

int main(int argc, char **argv) {

    visualizer = new Visualizer;
    visualizer-> init("Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);


    while (visualizer -> running()) {

        visualizer -> handleEvent();
        visualizer -> update() ;
        visualizer -> render() ;

    }

    visualizer -> clean() ;

    delete visualizer ;
    return 0;
}