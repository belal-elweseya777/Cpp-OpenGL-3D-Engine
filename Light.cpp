#include "Light.hpp"

Light::Light(GLenum id) : lightID(id), enabled(true), smoothShading(true) {
    position[0] = 4.0f; position[1] = 5.0f; position[2] = 5.0f; position[3] = 1.0f;
    ambient[0]  = 0.25f; ambient[1]  = 0.25f; ambient[2]  = 0.25f; ambient[3]  = 1.0f;
    diffuse[0]  = 0.85f; diffuse[1]  = 0.85f; diffuse[2]  = 0.85f; diffuse[3]  = 1.0f;
    specular[0] = 1.0f;  specular[1] = 1.0f;  specular[2] = 1.0f;  specular[3] = 1.0f;
}

void Light::setup() {
    glEnable(GL_LIGHTING);
    glEnable(lightID);
    glEnable(GL_NORMALIZE);

    // Enable color tracking so vertex colors interact with lighting material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat matSpecular[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);

    glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);
    apply();
}

void Light::apply() {
    if (!enabled) {
        glDisable(GL_LIGHTING);
        return;
    }

    glEnable(GL_LIGHTING);
    glEnable(lightID);
    glLightfv(lightID, GL_POSITION, position);
    glLightfv(lightID, GL_AMBIENT, ambient);
    glLightfv(lightID, GL_DIFFUSE, diffuse);
    glLightfv(lightID, GL_SPECULAR, specular);
}

void Light::setPosition(float x, float y, float z, float w) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = w;
}

void Light::toggle() {
    enabled = !enabled;
    if (enabled) {
        glEnable(GL_LIGHTING);
        glEnable(lightID);
    } else {
        glDisable(lightID);
        glDisable(GL_LIGHTING);
    }
}

void Light::toggleShadingModel() {
    smoothShading = !smoothShading;
    glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);
}