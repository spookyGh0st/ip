

#ifndef IP_CAMERA_H
#define IP_CAMERA_H


#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/fwd.hpp>

class Camera {
public:
    glm::vec3 position { 0,2,0 };
    glm::vec3 front {0,0,-1 };
    glm::vec3 up { 0,1,0};

    [[nodiscard]] glm::mat4 getViewMatrix() const;
    void update(float dt, float t);
private:

};


#endif //IP_CAMERA_H
