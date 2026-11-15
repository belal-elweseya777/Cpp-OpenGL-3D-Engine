#ifndef GAME_OBJECT_3D_HPP
#define GAME_OBJECT_3D_HPP

#include <SFML/OpenGL.hpp>

/**
 * @class GameObject3D
 * @brief Base class for all 3D entities supporting spatial transformations.
 */
class GameObject3D {
protected:
    float posX, posY, posZ;
    float rotX, rotY, rotZ;
    float scaleX, scaleY, scaleZ;

public:
    GameObject3D();
    virtual ~GameObject3D() {}

    void setPosition(float x, float y, float z);
    void translate(float dx, float dy, float dz);

    void setRotation(float rx, float ry, float rz);
    void rotate(float drx, float dry, float drz);

    void setScale(float sx, float sy, float sz);
    void scale(float factor);

    void applyTransformations() const;

    virtual void update(float deltaTime) = 0;
    virtual void draw() const = 0;
};

#endif // GAME_OBJECT_3D_HPP