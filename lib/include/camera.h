#pragma once
#include "Obj_visu.h"

class Camera
{
private:
    OBJ_VISU::Float3 initialPosition;
    OBJ_VISU::Float3 position;
    OBJ_VISU::Float3 nextMovement;
    float yaw;
    float pitch; 
    float deltapitch;
    float deltayaw;
    float fov;
    float screenWidth;
    float screenHeigth;
    float mouse_sensitivity = 0.005f;

public:
    Camera(float fov, OBJ_VISU::Float3 initialPosition, float screenWidth, float screenHeigth) : fov(fov), initialPosition(initialPosition), position(initialPosition), screenWidth(screenWidth), screenHeigth(screenHeigth) {pitch = 0.f; yaw = 0.f ;};
    ~Camera() {};

    void rotate();
    void move();
    OBJ_VISU::Float3 get_position() const { return position; }
    OBJ_VISU::Float3 getOrientationAxis() const;

    void calculatePositionOnScreen(OBJ_VISU::Point &point);
    void setNextMovement(OBJ_VISU::Float3 move) { nextMovement = move; };
    void setDeltaPitchAndYaw(float deltapitch, float deltayaw){
        this->deltapitch = deltapitch*mouse_sensitivity; 
        this->deltayaw = deltayaw*mouse_sensitivity;
    }
    void reset(){
        position = initialPosition;
        nextMovement= OBJ_VISU::Float3(0,0,0);
        yaw = 0;
        pitch = 0;
        deltapitch = 0;
        deltayaw = 0;
    }
};