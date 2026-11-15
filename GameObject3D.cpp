#include "GameObject3D.hpp"

GameObject3D::GameObject3D()
    : posX(0.0f), posY(0.0f), posZ(0.0f),
      rotX(0.0f), rotY(0.0f), rotZ(0.0f),
      scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f) {}

void GameObject3D::setPosition(float x, float y, float z) {
    posX = x; posY = y; posZ = z;
}

void GameObject3D::translate(float dx, float dy, float dz) {
    posX += dx; posY += dy; posZ += dz;
}

void GameObject3D::setRotation(float rx, float ry, float rz) {
    rotX = rx; rotY = ry; rotZ = rz;
}

void GameObject3D::rotate(float drx, float dry, float drz) {
    rotX += drx; rotY += dry; rotZ += drz;
}

void GameObject3D::setScale(float sx, float sy, float sz) {
    scaleX = sx; scaleY = sy; scaleZ = sz;
}

void GameObject3D::scale(float factor) {
    scaleX *= factor; scaleY *= factor; scaleZ *= factor;
}

void GameObject3D::applyTransformations() const {
    glTranslatef(posX, posY, posZ);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);
}