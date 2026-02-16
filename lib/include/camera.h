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
        float screenHeigth ;

    public:
        Camera(float fov, float screenWidth, float screenHeigth) :
                fov(fov), screenWidth(screenWidth), screenHeigth(screenHeigth) {};
        ~Camera(){};

        void rotate(float delta_yaw, float delta_pitch);
        void move(OBJ_VISU::Float3 delta_position);
        OBJ_VISU::Float3 get_position() const { return position; }

        void calculatePositionOnScreen(OBJ_VISU::Point& point) ;
    };