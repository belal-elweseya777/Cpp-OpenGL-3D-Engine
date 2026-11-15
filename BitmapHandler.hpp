#ifndef BITMAP_HANDLER_HPP
#define BITMAP_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>

/**
 * @class BitmapHandler
 * @brief Handles loading 2D image files and binding them as OpenGL textures.
 */
class BitmapHandler {
private:
    GLuint textureID;
    unsigned int width;
    unsigned int height;
    bool loaded;

public:
    BitmapHandler();
    ~BitmapHandler();

    bool loadFromFile(const std::string& filename);
    void generateProceduralCheckerboard(int size = 128);
    void bind() const;
    void unbind() const;
    GLuint getID() const { return textureID; }
    bool isLoaded() const { return loaded; }
};

#endif // BITMAP_HANDLER_HPP