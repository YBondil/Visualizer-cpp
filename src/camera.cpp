#include "camera.h"
#include <cmath>
#include <iostream>
void Camera::rotate(float delta_yaw, float delta_pitch){
    yaw += delta_yaw ;
    pitch += delta_pitch ;
}
void Camera::move(){
    
    position = position + nextMovement ;
    setNextMovement(OBJ_VISU::Float3(0,0,0));
    
}
void Camera::calculatePositionOnScreen(OBJ_VISU::Point& point){

    float x = point.getPosition().x - position.x;
    float y = point.getPosition().y - position.y;
    float z = point.getPosition().z - position.z;
    
    // Rotation Yaw
    float tmp_x = x * cos(yaw) - z * sin(yaw);
    float tmp_z = x * sin(yaw) + z * cos(yaw);
    x = tmp_x;
    z = tmp_z;

    // Rotation Pitch
    float tmp_y = y * cos(pitch) - z * sin(pitch);
    z = y * sin(pitch) + z * cos(pitch); 
    y = tmp_y;

    if (z < 0.1f) {
        point.setPositionOnScreen(-1000.f, -1000.f) ;
        return ;
    }
    float fov_radians = fov * (M_PI / 180.0f);
    float f = 1.0f / tan(fov_radians / 2.0f);
    
    float ratio = screenWidth / screenHeigth;

    // normalisation
    float xp = (x * f) / (ratio * z);
    float yp = (y * f) / z; 

    float final_x = (xp + 1.0f) * (screenWidth / 2.0f);
    float final_y = (1.0f - yp) * (screenHeigth / 2.0f);

    point.setPositionOnScreen(final_x, final_y);
    return ;
}