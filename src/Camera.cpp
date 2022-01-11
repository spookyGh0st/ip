#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position,position+front, up);
}

void Camera::update(float dt, float t) {
    position.x = 5.0f*sinf(0.2f*t);
    position.y = 2.0f+1.5f*cosf(0.05f*t);
    position.z = -5+2.0f*sinf(0.1f*t);
}
