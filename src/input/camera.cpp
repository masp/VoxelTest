#include "input/camera.hpp"

Camera::Camera(glm::vec3 pos) : _pos(pos), _pitch(0.0f), _yaw(0.0f), _fov(45.0f), _aspRatio(3.0f / 2.0f), _far(1000.0f), _near(0.1f), _proj(glm::perspective(_fov, _aspRatio, _near, _far)) 
{
}

void Camera::changeLook(float pitch, float yaw)
{
    _pitch += pitch;
    _yaw += yaw;
    fixAngles();
}

const glm::mat4 Camera::rotation() const
{
    glm::mat4 rot;
    rot = glm::rotate(rot, _pitch, glm::vec3(1.0, 0.0, 0.0)); 
    rot = glm::rotate(rot, _yaw, glm::vec3(0.0, 1.0, 0.0));
    return rot;
}

void Camera::fixAngles()
{
    _yaw = fmodf(_yaw, 360.0f);

    if (_yaw < 0.0f)
	_yaw += 360.0f;

    if (_pitch > 85.0f) {
	_pitch = 85.0f;
    } else if (_pitch < -85.0f) {
	_pitch = -85.0f;
    }
}

void Camera::reset()
{
	changeLook(-_pitch, -_yaw);
}

void Camera::setAspectRatio(float aspRatio)
{
    _aspRatio = aspRatio;
    recalcProjection();
}

void Camera::setFov(float fov)
{
    _fov = fov;
    recalcProjection();
}

void Camera::setFar(float far)
{
    _far = far;
    recalcProjection();
}

void Camera::setNear(float near)
{
    _near = near;
    recalcProjection();
}

void Camera::recalcProjection()
{
    _proj = glm::perspective(_fov, _aspRatio, _near, _far);
}

const glm::mat4 Camera::matrix() const
{
   return projection() * (rotation() * glm::translate(glm::mat4(), -_pos));  
}

glm::vec3 Camera::right() const
{
    glm::vec4 vect4 = glm::inverse(rotation()) * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    return glm::vec3(vect4);
}

glm::vec3 Camera::up() const
{
    glm::vec4 vect4 = glm::inverse(rotation()) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    return glm::vec3(vect4);
}

glm::vec3 Camera::forward() const
{
    glm::vec4 vect4 = glm::inverse(rotation()) * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    return glm::vec3(vect4);
}
