#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <SFML/OpenGL.hpp>

/**
 * @class Light
 * @brief Encapsulates OpenGL Phong lighting parameters and shading modes.
 */
class Light {
private:
    GLenum lightID;
    GLfloat position[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    bool enabled;
    bool smoothShading;

public:
    Light(GLenum id = GL_LIGHT0);

    void setup();
    void apply();
    void setPosition(float x, float y, float z, float w = 1.0f);
    void toggle();
    void toggleShadingModel();
    bool isEnabled() const { return enabled; }
    bool isSmoothShading() const { return smoothShading; }
};

#endif // LIGHT_HPP