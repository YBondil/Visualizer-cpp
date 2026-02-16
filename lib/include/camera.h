#pragma once 
#include "Obj_visu.h"

class Camera
    {
    private:
        OBJ_VISU::Float3 position ;
        float yaw = 0.f ;
        float pitch = 0.f ;
        float fov ;
        float screenWidth ;
        float screenHeight ;

    public:
        Camera(float fov, float screenWidth, float screenHeigth) : 
            fov(fov), screenHeight(screenHeight), screenWidth(screenWidth) {};
        ~Camera(){};

        void rotate(int delta_yaw, int delta_pitch);
        void move(OBJ_VISU::Float3 delta_position);
        OBJ_VISU::Float3 get_position() const { return position; }

        SDL_FPoint calculatePositionOnScreen(OBJ_VISU::Point& point) ;
    };