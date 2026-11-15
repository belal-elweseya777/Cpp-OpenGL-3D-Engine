#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/OpenGL.hpp>
#include <cmath>

/**
 * @class Camera
 * @brief Observer class managing 3D view transformation and movement.
 */
class Camera {
private:
    float posX, posY, posZ;
    float targetX, targetY, targetZ;
    float upX, upY, upZ;
    float yaw;
    float pitch;
    float moveSpeed;

    void updateVectors();

public:
    Camera(float x = 0.0f, float y = 2.0f, float z = 6.0f);

    void applyView() const;
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
    void rotate(float deltaYaw, float deltaPitch);
    void reset();
};

#endif // CAMERA_HPP