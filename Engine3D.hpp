#ifndef ENGINE3D_HPP
#define ENGINE3D_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <string>
#include "Camera.hpp"
#include "Light.hpp"
#include "BitmapHandler.hpp"
#include "Cube.hpp"
#include "Pyramid.hpp"
#include "Sphere.hpp"

/**
 * @class Engine3D
 * @brief Main 3D Game Engine framework managing windowing, projections, lighting, and scene objects.
 */
class Engine3D {
private:
    int windowWidth;
    int windowHeight;
    std::string windowTitle;
    sf::RenderWindow window;
    bool isRunning;
    bool isPerspective;
    bool texturesEnabled;
    bool pauseAnimation;

    Camera camera;
    Light mainLight;
    BitmapHandler crateTexture;
    BitmapHandler floorTexture;

    std::vector<GameObject3D*> sceneObjects;
    Cube* centerCube;
    Pyramid* floatingPyramid;
    Sphere* metallicSphere;
    Sphere* lightOrb;

    float sceneTime;
    float speedMultiplier;

    void handleEvents();
    void handleContinuousInput(float deltaTime);
    void update(float deltaTime);
    void render();
    void drawTexturedFloor() const;
    void drawCoordinateAxes() const;

public:
    Engine3D(int width, int height, const std::string& title);
    virtual ~Engine3D();

    void init();
    void run();
    void setupProjection();
    void toggleProjection();
};

#endif // ENGINE3D_HPP