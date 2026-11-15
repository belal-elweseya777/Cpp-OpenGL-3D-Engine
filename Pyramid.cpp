#include "Pyramid.hpp"

namespace {
    // 16 vertices (4 triangular faces * 3 + 1 square base * 4) for crisp face normals
    const GLfloat pyramidVertices[] = {
        // Front face (+Z)
        -0.5f, 0.0f,  0.5f,   0.5f, 0.0f,  0.5f,   0.0f, 1.0f,  0.0f,
        // Right face (+X)
         0.5f, 0.0f,  0.5f,   0.5f, 0.0f, -0.5f,   0.0f, 1.0f,  0.0f,
        // Back face (-Z)
         0.5f, 0.0f, -0.5f,  -0.5f, 0.0f, -0.5f,   0.0f, 1.0f,  0.0f,
        // Left face (-X)
        -0.5f, 0.0f, -0.5f,  -0.5f, 0.0f,  0.5f,   0.0f, 1.0f,  0.0f,
        // Base (-Y)
        -0.5f, 0.0f, -0.5f,   0.5f, 0.0f, -0.5f,   0.5f, 0.0f,  0.5f,  -0.5f, 0.0f,  0.5f
    };

    const GLfloat pyramidNormals[] = {
         0.0f,  0.447f,  0.894f,   0.0f,  0.447f,  0.894f,   0.0f,  0.447f,  0.894f,
         0.894f, 0.447f,  0.0f,    0.894f, 0.447f,  0.0f,    0.894f, 0.447f,  0.0f,
         0.0f,  0.447f, -0.894f,   0.0f,  0.447f, -0.894f,   0.0f,  0.447f, -0.894f,
        -0.894f, 0.447f,  0.0f,   -0.894f, 0.447f,  0.0f,   -0.894f, 0.447f,  0.0f,
         0.0f, -1.0f,    0.0f,     0.0f, -1.0f,    0.0f,     0.0f, -1.0f,    0.0f,     0.0f, -1.0f, 0.0f
    };

    const GLfloat pyramidColors[] = {
        1.0f, 0.84f, 0.0f,  1.0f, 0.75f, 0.0f,  1.0f, 0.95f, 0.4f,
        0.9f, 0.70f, 0.0f,  0.8f, 0.60f, 0.0f,  1.0f, 0.95f, 0.4f,
        1.0f, 0.84f, 0.0f,  1.0f, 0.75f, 0.0f,  1.0f, 0.95f, 0.4f,
        0.9f, 0.70f, 0.0f,  0.8f, 0.60f, 0.0f,  1.0f, 0.95f, 0.4f,
        0.6f, 0.45f, 0.1f,  0.6f, 0.45f, 0.1f,  0.6f, 0.45f, 0.1f,  0.6f, 0.45f, 0.1f
    };

    const GLfloat pyramidTexCoords[] = {
        0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f
    };

    const GLubyte pyramidIndices[] = {
         0,  1,  2,
         3,  4,  5,
         6,  7,  8,
         9, 10, 11,
        12, 13, 14,  14, 15, 12
    };
}

Pyramid::Pyramid(float size) : texture(nullptr), useTexture(true), autoRotateSpeed(25.0f) {
    setScale(size, size, size);
}

void Pyramid::update(float deltaTime) {
    rotate(0.0f, autoRotateSpeed * deltaTime, 0.0f);
}

void Pyramid::draw() const {
    glPushMatrix();
    applyTransformations();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pyramidVertices);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, pyramidNormals);

    if (useTexture && texture != nullptr && texture->isLoaded()) {
        glColor3f(1.0f, 0.92f, 0.7f);
        texture->bind();
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, pyramidTexCoords);
    } else {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, pyramidColors);
    }

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, pyramidIndices);

    if (useTexture && texture != nullptr && texture->isLoaded()) {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        texture->unbind();
    } else {
        glDisableClientState(GL_COLOR_ARRAY);
    }

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}