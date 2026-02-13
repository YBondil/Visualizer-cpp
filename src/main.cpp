#include "visualizer.h"

VISU::Visualizer * visualizer ;
int heigth = 500 ;
int width = 500 ;
bool fullscreen = false ;

VISU::Object* ligne;
int main(int argc, char **argv) {

    visualizer = new VISU::Visualizer;
    ligne = new VISU::Object ;

    ligne -> init(50,50);

    visualizer -> init("Visualizer", heigth, width, fullscreen);
    visualizer -> add_object(*ligne) ;

    while (visualizer -> running()) {

        visualizer -> handleEvent();
        visualizer -> update() ;
        visualizer -> render() ;

    }

    visualizer -> clean() ;

    delete visualizer ;
    return 0;
}