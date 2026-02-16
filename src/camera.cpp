#include "camera.h"
#include <cmath>

void Camera::rotate(int delta_yaw, int delta_pitch){
    yaw += delta_yaw ;
    pitch += delta_pitch ;
}
void Camera::move(OBJ_VISU::Float3 delta_position){
    position = position + delta_position ;
}
SDL_FPoint Camera::calculatePositionOnScreen(OBJ_VISU::Point& point){

    float x = point.getPosition().x - position.x ;
    float y = point.getPosition().y - position.y ;
    float z = point.getPosition().z - position.z ;
    
    //rotation yaw
    x = x*cos(yaw) - z*sin(yaw) ;
    z = x*sin(yaw) + z*cos(yaw) ;

    //rotation pitch
    y = y*cos(pitch) - z*sin(pitch) ;
    z = y*sin(yaw) + z*cos(pitch) ;

    if (z<0.1f){
        return ;
    }

    float f = 1/tan(fov/2.f);
    float ratio = screenWidth/screenHeight ;

    float xp = x*(f/ratio)/z ;
    float yp = y*f/z ; 

    xp = (x + 1.f)*screenHeight/2.f ;
    yp = (1.f - yp)*screenHeight/2.f ;

    point.setPositionOnScreen(xp,yp) ;
    return ;

}