#include "BitmapHandler.hpp"
#include <vector>

BitmapHandler::BitmapHandler() : textureID(0), width(0), height(0), loaded(false) {}

BitmapHandler::~BitmapHandler() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

bool BitmapHandler::loadFromFile(const std::string& filename) {
    sf::Image image;
    if (!image.loadFromFile(filename)) {
        std::cerr << "[BitmapHandler] Warning: Could not load '" << filename << "'. Generating fallback texture.\n";
        generateProceduralCheckerboard();
        return false;
    }

    image.flipVertically();
    width = image.getSize().x;
    height = image.getSize().y;

    if (textureID == 0) {
        glGenTextures(1, &textureID);
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
    loaded = true;
    return true;
}

void BitmapHandler::generateProceduralCheckerboard(int size) {
    width = size;
    height = size;
    std::vector<GLubyte> pixels(size * size * 4);

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            bool isWhite = ((x / 16) + (y / 16)) % 2 == 0;
            int idx = (y * size + x) * 4;
            pixels[idx + 0] = isWhite ? 230 : 45;
            pixels[idx + 1] = isWhite ? 230 : 95;
            pixels[idx + 2] = isWhite ? 235 : 165;
            pixels[idx + 3] = 255;
        }
    }

    if (textureID == 0) {
        glGenTextures(1, &textureID);
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
    loaded = true;
}

void BitmapHandler::bind() const {
    if (loaded && textureID != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
}

void BitmapHandler::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}