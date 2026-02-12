#include <iostream>
#include "../lib/SDL/SDL.h"

#define NON 0 
#define OUI 1
void pause(void) ;

int main (int argc , char ** argv){
    DL_Surface * screen ; /* déclaration de la variable ecran, ou fenêtre, ici appelée screen */
    SDL_Init(SDL_INIT_VIDEO) ;
    screen= SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE) ; 
    SDL_WM_SetCaption(« ECRAN NOIR »,NULL) ; 
    SDL_Flip(screen) ;  
    pause() ; 
    return 0 ;
}
void pause(){ 
    int continuer=OUI;
    SDL_Event event; 3
    while(continuer== OUI){ 
        SDL_WaitEvent(&event);
        if (event.type==SDL_QUIT) {
            continuer=NON;
        }
    }
}

