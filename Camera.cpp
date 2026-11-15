#include "Camera.hpp"
#include <GL/glu.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camera::Camera(float x, float y, float z)
    : posX(x), posY(y), posZ(z),
      upX(0.0f), upY(1.0f), upZ(0.0f),
      yaw(-90.0f), pitch(-15.0f), moveSpeed(5.0f) {
    updateVectors();
}

void Camera::updateVectors() {
    float radYaw = yaw * static_cast<float>(M_PI) / 180.0f;
    float radPitch = pitch * static_cast<float>(M_PI) / 180.0f;

    float frontX = std::cos(radYaw) * std::cos(radPitch);
    float frontY = std::sin(radPitch);
    float frontZ = std::sin(radYaw) * std::cos(radPitch);

    targetX = posX + frontX;
    targetY = posY + frontY;
    targetZ = posZ + frontZ;
}

void Camera::applyView() const {
    float fx = targetX - posX;
    float fy = targetY - posY;
    float fz = targetZ - posZ;
    float fLen = std::sqrt(fx * fx + fy * fy + fz * fz);
    if (fLen > 0.0001f) { fx /= fLen; fy /= fLen; fz /= fLen; }

    // s = f x up
    float sx = fy * upZ - fz * upY;
    float sy = fz * upX - fx * upZ;
    float sz = fx * upY - fy * upX;
    float sLen = std::sqrt(sx * sx + sy * sy + sz * sz);
    if (sLen > 0.0001f) { sx /= sLen; sy /= sLen; sz /= sLen; }

    // u = s x f
    float ux = sy * fz - sz * fy;
    float uy = sz * fx - sx * fz;
    float uz = sx * fy - sy * fx;

    GLfloat m[16] = {
         sx,  ux, -fx, 0.0f,
         sy,  uy, -fy, 0.0f,
         sz,  uz, -fz, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    glMultMatrixf(m);
    glTranslatef(-posX, -posY, -posZ);
}

void Camera::moveForward(float deltaTime) {
    float dirX = targetX - posX;
    float dirY = targetY - posY;
    float dirZ = targetZ - posZ;
    posX += dirX * moveSpeed * deltaTime;
    posY += dirY * moveSpeed * deltaTime;
    posZ += dirZ * moveSpeed * deltaTime;
    updateVectors();
}

void Camera::moveBackward(float deltaTime) {
    float dirX = targetX - posX;
    float dirY = targetY - posY;
    float dirZ = targetZ - posZ;
    posX -= dirX * moveSpeed * deltaTime;
    posY -= dirY * moveSpeed * deltaTime;
    posZ -= dirZ * moveSpeed * deltaTime;
    updateVectors();
}

void Camera::moveLeft(float deltaTime) {
    float dirX = targetX - posX;
    float dirZ = targetZ - posZ;
    float rightX = -dirZ;
    float rightZ = dirX;
    posX -= rightX * moveSpeed * deltaTime;
    posZ -= rightZ * moveSpeed * deltaTime;
    updateVectors();
}

void Camera::moveRight(float deltaTime) {
    float dirX = targetX - posX;
    float dirZ = targetZ - posZ;
    float rightX = -dirZ;
    float rightZ = dirX;
    posX += rightX * moveSpeed * deltaTime;
    posZ += rightZ * moveSpeed * deltaTime;
    updateVectors();
}

void Camera::moveUp(float deltaTime) {
    posY += moveSpeed * deltaTime;
    updateVectors();
}

void Camera::moveDown(float deltaTime) {
    posY -= moveSpeed * deltaTime;
    updateVectors();
}

void Camera::rotate(float deltaYaw, float deltaPitch) {
    yaw += deltaYaw;
    pitch += deltaPitch;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    updateVectors();
}

void Camera::reset() {
    posX = 0.0f; posY = 2.0f; posZ = 6.0f;
    yaw = -90.0f; pitch = -15.0f;
    updateVectors();
}