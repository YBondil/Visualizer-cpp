#include "camera.h"
#include <cmath>
#include <iostream>
void Camera::rotate()
{
    yaw += deltayaw;
    pitch += deltapitch;
    deltapitch = 0;
    deltayaw = 0;
}
void Camera::move()
{

    position = position + nextMovement;
    setNextMovement(OBJ_VISU::Float3());
}
void Camera::calculatePositionOnScreen(OBJ_VISU::Point &point)
{

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

    if (z < 0.1f)
    {
        point.setPositionOnScreen(-1000.f, -1000.f);
        return;
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
    return;
}

void Camera::reset()
{
    position = initialPosition;
    nextMovement = OBJ_VISU::Float3();
    yaw = 0;
    pitch = 0;
    deltapitch = 0;
    deltayaw = 0;
}

void Camera::updateOrbitPosition()
{
    position.x = orbitTarget.x - orbitDistance * std::cos(pitch) * std::sin(yaw);
    position.y = orbitTarget.y - orbitDistance * std::sin(pitch);
    position.z = orbitTarget.z - orbitDistance * std::cos(pitch) * std::cos(yaw);
}

void Camera::pan(float delta_x, float delta_y)
{
    // calcul axe d'observation
    OBJ_VISU::Float3 forward;
    forward.x = std::cos(pitch) * std::sin(yaw);
    forward.y = std::sin(pitch);
    forward.z = std::cos(pitch) * std::cos(yaw);
    forward.normalize();

    // calcul de la des axes de la cam
    OBJ_VISU::Float3 worldUp(0.0f, 1.0f, 0.0f);

    OBJ_VISU::Float3 right = worldUp.crossProduct(forward);
    right.normalize();

    OBJ_VISU::Float3 up = forward.crossProduct(right);
    up.normalize();

    float pan_speed = 0.05;

    orbitTarget = orbitTarget + right * (-delta_x * pan_speed) + up * (delta_y * pan_speed);
}