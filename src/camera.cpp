#include "camera.h"
#include <cmath>

void Camera::rotate(float delta_yaw, float delta_pitch){
    yaw += delta_yaw ;
    pitch += delta_pitch ;
}
void Camera::move(OBJ_VISU::Float3 delta_position){
    position = position + delta_position ;
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
    float f = 1.0f / tan(fov / 2.0f);
    float ratio = screenWidth / screenHeight;

    // normalisation
    float xp = (x * f) / (ratio * z);
    float yp = (y * f) / z; 

    float final_x = (xp + 1.0f) * (screenWidth / 2.0f);
    float final_y = (1.0f - yp) * (screenHeight / 2.0f);

    point.setPositionOnScreen(final_x, final_y);
    return ;
}