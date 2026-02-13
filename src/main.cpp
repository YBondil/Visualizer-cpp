#include "visualizer.h"

VISU::Visualizer * visualizer ;

int main(int argc, char **argv) {

    visualizer = new VISU::Visualizer;
    visualizer -> init("Visualizer", 600, 800, false);

    while (visualizer -> running()) {

        visualizer -> handleEvent();
        visualizer -> update() ;
        visualizer -> render() ;

    }

    visualizer -> clean() ;

    delete visualizer ;
    return 0;
}