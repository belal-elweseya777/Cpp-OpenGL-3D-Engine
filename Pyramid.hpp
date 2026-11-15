#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include "GameObject3D.hpp"
#include "BitmapHandler.hpp"

/**
 * @class Pyramid
 * @brief Indexed 3D Square-Based Pyramid with Normals, Colors, and Texture Coordinates.
 */
class Pyramid : public GameObject3D {
private:
    BitmapHandler* texture;
    bool useTexture;
    float autoRotateSpeed;

public:
    Pyramid(float size = 1.0f);
    virtual ~Pyramid() {}

    void setTexture(BitmapHandler* tex) { texture = tex; }
    void toggleTexture() { useTexture = !useTexture; }
    void setAutoRotateSpeed(float speed) { autoRotateSpeed = speed; }

    void update(float deltaTime) override;
    void draw() const override;
};

#endif // PYRAMID_HPP