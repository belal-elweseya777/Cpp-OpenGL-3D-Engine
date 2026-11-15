#ifndef CUBE_HPP
#define CUBE_HPP

#include "GameObject3D.hpp"
#include "BitmapHandler.hpp"

/**
 * @class Cube
 * @brief Indexed 3D Cube implementing Vertex, Normal, Color, and Texture Coordinate arrays.
 */
class Cube : public GameObject3D {
private:
    BitmapHandler* texture;
    bool useTexture;
    float autoRotateSpeed;

public:
    Cube(float size = 1.0f);
    virtual ~Cube() {}

    void setTexture(BitmapHandler* tex);
    void toggleTexture();
    void setAutoRotateSpeed(float speed) { autoRotateSpeed = speed; }

    void update(float deltaTime) override;
    void draw() const override;
};

#endif // CUBE_HPP