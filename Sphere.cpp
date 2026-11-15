#include "Sphere.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Sphere::Sphere(float radius, int sectors, int stacks)
    : colorR(0.2f), colorG(0.75f), colorB(0.95f), emissive(false) {
    generateMesh(radius, sectors, stacks);
}

void Sphere::generateMesh(float radius, int sectors, int stacks) {
    vertices.clear();
    normals.clear();
    indices.clear();

    float lengthInv = 1.0f / radius;
    float sectorStep = 2.0f * static_cast<float>(M_PI) / sectors;
    float stackStep = static_cast<float>(M_PI) / stacks;

    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = static_cast<float>(M_PI) / 2.0f - i * stackStep;
        float xy = radius * std::cos(stackAngle);
        float z = radius * std::sin(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * sectorStep;
            float x = xy * std::cos(sectorAngle);
            float y = xy * std::sin(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            normals.push_back(x * lengthInv);
            normals.push_back(y * lengthInv);
            normals.push_back(z * lengthInv);
        }
    }

    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void Sphere::setColor(float r, float g, float b) {
    colorR = r; colorG = g; colorB = b;
}

void Sphere::update(float deltaTime) {
    rotate(0.0f, 20.0f * deltaTime, 0.0f);
}

void Sphere::draw() const {
    glPushMatrix();
    applyTransformations();

    GLboolean lightingEnabled = glIsEnabled(GL_LIGHTING);
    if (emissive && lightingEnabled) {
        glDisable(GL_LIGHTING);
    }

    glColor3f(colorR, colorG, colorB);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals.data());

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    if (emissive && lightingEnabled) {
        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
}
