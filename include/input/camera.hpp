#ifndef _MAKESHIFT_CAMERA_HPP_
#define _MAKESHIFT_CAMERA_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:
    Camera(glm::vec3 pos); 

    // Camera Positioning 
    inline void setPosition(glm::vec3 pos) { _pos = pos; }
    inline void move(glm::vec3 offset) { _pos += offset; }
    inline const glm::vec3 position() const { return _pos; }

    void changeLook(float pitch, float yaw);
	void reset();
    const glm::mat4 rotation() const;

    // Projection Setting Modifications
    void setFov(float fov);
    void setAspectRatio(float ratio);
    void setFar(float far);
    void setNear(float near);
    inline const glm::mat4 projection() const { return _proj; }

    glm::vec3 right() const;
    glm::vec3 up() const;
    glm::vec3 forward() const;

    const glm::mat4 matrix() const;

private:
    void recalcProjection();
    void fixAngles();

    glm::vec3 _pos;

    float _pitch;
    float _yaw;

    float _fov;
    float _aspRatio;
    float _far;
    float _near;
    glm::mat4 _proj;
};

#endif
