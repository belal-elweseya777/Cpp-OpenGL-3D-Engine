#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "GameObject3D.hpp"
#include <vector>

/**
 * @class Sphere
 * @brief Procedural 3D UV-Sphere supporting Smooth/Flat shading and emissive light-orb mode.
 */
class Sphere : public GameObject3D {
private:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLuint> indices;

    float colorR, colorG, colorB;
    bool emissive;

    void generateMesh(float radius, int sectors, int stacks);

public:
    Sphere(float radius = 0.5f, int sectors = 24, int stacks = 16);
    virtual ~Sphere() {}

    void setColor(float r, float g, float b);
    void setEmissive(bool isEmissive) { emissive = isEmissive; }

    void update(float deltaTime) override;
    void draw() const override;
};

#endif // SPHERE_HPP
