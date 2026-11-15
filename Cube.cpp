#include "Cube.hpp"

namespace {
    // 24 vertices (4 per face for crisp normals and UV mapping)
    const GLfloat cubeVertices[] = {
        // Front face (+Z)
        -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
        // Back face (-Z)
         0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,   0.5f,  0.5f, -0.5f,
        // Top face (+Y)
        -0.5f,  0.5f,  0.5f,   0.5f,  0.5f,  0.5f,   0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
        // Bottom face (-Y)
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,
        // Right face (+X)
         0.5f, -0.5f,  0.5f,   0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,
        // Left face (-X)
        -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f
    };

    const GLfloat cubeNormals[] = {
         0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,
         0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,
         0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,
         1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f
    };

    const GLfloat cubeColors[] = {
        1.0f, 0.3f, 0.3f,  1.0f, 0.3f, 0.3f,  1.0f, 0.3f, 0.3f,  1.0f, 0.3f, 0.3f,
        0.3f, 1.0f, 0.3f,  0.3f, 1.0f, 0.3f,  0.3f, 1.0f, 0.3f,  0.3f, 1.0f, 0.3f,
        0.3f, 0.5f, 1.0f,  0.3f, 0.5f, 1.0f,  0.3f, 0.5f, 1.0f,  0.3f, 0.5f, 1.0f,
        1.0f, 1.0f, 0.3f,  1.0f, 1.0f, 0.3f,  1.0f, 1.0f, 0.3f,  1.0f, 1.0f, 0.3f,
        1.0f, 0.4f, 1.0f,  1.0f, 0.4f, 1.0f,  1.0f, 0.4f, 1.0f,  1.0f, 0.4f, 1.0f,
        0.3f, 1.0f, 1.0f,  0.3f, 1.0f, 1.0f,  0.3f, 1.0f, 1.0f,  0.3f, 1.0f, 1.0f
    };

    const GLfloat cubeTexCoords[] = {
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f
    };

    const GLubyte cubeIndices[] = {
         0,  1,  2,   2,  3,  0, // Front
         4,  5,  6,   6,  7,  4, // Back
         8,  9, 10,  10, 11,  8, // Top
        12, 13, 14,  14, 15, 12, // Bottom
        16, 17, 18,  18, 19, 16, // Right
        20, 21, 22,  22, 23, 20  // Left
    };
}

Cube::Cube(float size) : texture(nullptr), useTexture(true), autoRotateSpeed(30.0f) {
    setScale(size, size, size);
}

void Cube::setTexture(BitmapHandler* tex) {
    texture = tex;
}

void Cube::toggleTexture() {
    useTexture = !useTexture;
}

void Cube::update(float deltaTime) {
    rotate(0.0f, autoRotateSpeed * deltaTime, 0.0f);
}

void Cube::draw() const {
    glPushMatrix();
    applyTransformations();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);

    if (useTexture && texture != nullptr && texture->isLoaded()) {
        glColor3f(1.0f, 1.0f, 1.0f);
        texture->bind();
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, cubeTexCoords);
    } else {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, cubeColors);
    }

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubeIndices);

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