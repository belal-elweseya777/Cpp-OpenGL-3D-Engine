#include "Engine3D.hpp"
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Engine3D::Engine3D(int width, int height, const std::string& title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
      isRunning(false), isPerspective(true), texturesEnabled(true), pauseAnimation(false),
      centerCube(nullptr), floatingPyramid(nullptr), metallicSphere(nullptr), lightOrb(nullptr),
      sceneTime(0.0f), speedMultiplier(1.0f) {}

Engine3D::~Engine3D() {
    for (auto* obj : sceneObjects) {
        delete obj;
    }
    sceneObjects.clear();
}

void Engine3D::init() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 2;
    settings.minorVersion = 1;

    window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.06f, 0.07f, 0.11f, 1.0f);

    setupProjection();
    mainLight.setup();

    crateTexture.loadFromFile("texture.png");
    floorTexture.generateProceduralCheckerboard(256);

    // 1. Central Pedestal Cube
    centerCube = new Cube(1.6f);
    centerCube->setPosition(0.0f, 0.8f, 0.0f);
    centerCube->setTexture(&crateTexture);
    centerCube->setAutoRotateSpeed(20.0f);
    sceneObjects.push_back(centerCube);

    // 2. Floating Golden Pyramid above the central pedestal
    floatingPyramid = new Pyramid(1.2f);
    floatingPyramid->setPosition(0.0f, 2.1f, 0.0f);
    floatingPyramid->setTexture(&crateTexture);
    floatingPyramid->setAutoRotateSpeed(-45.0f);
    sceneObjects.push_back(floatingPyramid);

    // 3. Orbiting Metallic Sphere demonstrating Smooth Phong Specular Highlights
    metallicSphere = new Sphere(0.65f, 32, 24);
    metallicSphere->setPosition(3.0f, 1.0f, 0.0f);
    metallicSphere->setColor(0.15f, 0.75f, 0.95f);
    sceneObjects.push_back(metallicSphere);

    // 4. Four Corner Architectural Pillars
    float pillarPositions[4][2] = { {-4.2f, -4.2f}, {4.2f, -4.2f}, {-4.2f, 4.2f}, {4.2f, 4.2f} };
    for (int i = 0; i < 4; ++i) {
        Cube* pillar = new Cube(1.0f);
        pillar->setScale(0.6f, 2.8f, 0.6f);
        pillar->setPosition(pillarPositions[i][0], 1.4f, pillarPositions[i][1]);
        pillar->setTexture(&crateTexture);
        pillar->setAutoRotateSpeed(0.0f);
        sceneObjects.push_back(pillar);
    }

    // 5. Visual Orbiting Light Source Orb
    lightOrb = new Sphere(0.22f, 16, 12);
    lightOrb->setColor(1.0f, 0.95f, 0.6f);
    lightOrb->setEmissive(true);
    sceneObjects.push_back(lightOrb);

    std::cout << "=====================================================\n"
              << "       3D GAME ENGINE FRAMEWORK - CONTROLS\n"
              << "=====================================================\n"
              << " W / A / S / D : Move Camera Horizontally\n"
              << " Q / E         : Move Camera Up / Down\n"
              << " Arrow Keys    : Rotate Camera (Yaw / Pitch)\n"
              << " P             : Toggle Perspective / Orthogonal\n"
              << " L             : Toggle Phong Lighting\n"
              << " F             : Toggle Smooth / Flat Shading\n"
              << " T             : Toggle 2D Texture Mapping\n"
              << " Space         : Pause / Resume Scene Animation\n"
              << " + / -         : Increase / Decrease Simulation Speed\n"
              << " R             : Reset Camera to Default View\n"
              << " ESC           : Exit Application\n"
              << "=====================================================\n";

    isRunning = true;
}

void Engine3D::setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight > 0 ? windowHeight : 1);

    if (isPerspective) {
        GLdouble fov = 60.0;
        GLdouble nearZ = 0.1;
        GLdouble farZ = 100.0;
        GLdouble fH = std::tan(fov / 360.0 * M_PI) * nearZ;
        GLdouble fW = fH * aspect;
        glFrustum(-fW, fW, -fH, fH, nearZ, farZ);
    } else {
        float orthoSize = 5.5f;
        glOrtho(-orthoSize * aspect, orthoSize * aspect, -orthoSize, orthoSize, -50.0, 50.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

void Engine3D::toggleProjection() {
    isPerspective = !isPerspective;
    setupProjection();
}

void Engine3D::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
        } else if (event.type == sf::Event::Resized) {
            windowWidth = event.size.width;
            windowHeight = event.size.height;
            glViewport(0, 0, windowWidth, windowHeight);
            setupProjection();
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape: isRunning = false; break;
                case sf::Keyboard::P: toggleProjection(); break;
                case sf::Keyboard::L: mainLight.toggle(); break;
                case sf::Keyboard::F: mainLight.toggleShadingModel(); break;
                case sf::Keyboard::T:
                    texturesEnabled = !texturesEnabled;
                    if (centerCube) centerCube->toggleTexture();
                    if (floatingPyramid) floatingPyramid->toggleTexture();
                    break;
                case sf::Keyboard::Space: pauseAnimation = !pauseAnimation; break;
                case sf::Keyboard::Add:
                case sf::Keyboard::Equal: speedMultiplier += 0.25f; break;
                case sf::Keyboard::Subtract:
                case sf::Keyboard::Dash:
                    speedMultiplier = (speedMultiplier > 0.25f) ? speedMultiplier - 0.25f : 0.0f;
                    break;
                case sf::Keyboard::R: camera.reset(); break;
                default: break;
            }
        }
    }
}

void Engine3D::handleContinuousInput(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.moveForward(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.moveBackward(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.moveLeft(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.moveRight(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) camera.moveUp(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) camera.moveDown(deltaTime);

    float rotSpeed = 65.0f * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  camera.rotate(-rotSpeed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) camera.rotate(rotSpeed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    camera.rotate(0.0f, rotSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  camera.rotate(0.0f, -rotSpeed);
}

void Engine3D::update(float deltaTime) {
    handleContinuousInput(deltaTime);

    if (pauseAnimation) return;

    float simDelta = deltaTime * speedMultiplier;
    sceneTime += simDelta;

    // Gentle levitation for the golden pyramid
    if (floatingPyramid) {
        floatingPyramid->setPosition(0.0f, 2.0f + std::sin(sceneTime * 2.5f) * 0.25f, 0.0f);
    }

    // Orbit the metallic sphere around the pedestal
    if (metallicSphere) {
        metallicSphere->setPosition(std::cos(sceneTime * 1.1f) * 2.8f, 1.0f, std::sin(sceneTime * 1.1f) * 2.8f);
    }

    // Orbit the light source overhead so specular highlights dynamically shift across surfaces
    float lx = std::cos(sceneTime * 0.8f) * 3.8f;
    float ly = 4.2f;
    float lz = std::sin(sceneTime * 0.8f) * 3.8f;
    mainLight.setPosition(lx, ly, lz, 1.0f);
    if (lightOrb) {
        lightOrb->setPosition(lx, ly, lz);
    }

    for (auto* obj : sceneObjects) {
        obj->update(simDelta);
    }
}

void Engine3D::drawTexturedFloor() const {
    if (texturesEnabled && floorTexture.isLoaded()) {
        floorTexture.bind();
        glColor3f(0.75f, 0.78f, 0.85f);
    } else {
        glColor3f(0.22f, 0.25f, 0.30f);
    }

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.5f, 0.0f,  5.5f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f( 5.5f, 0.0f,  5.5f);
    glTexCoord2f(4.0f, 4.0f); glVertex3f( 5.5f, 0.0f, -5.5f);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(-5.5f, 0.0f, -5.5f);
    glEnd();

    if (texturesEnabled && floorTexture.isLoaded()) {
        floorTexture.unbind();
    }
}

void Engine3D::drawCoordinateAxes() const {
    GLboolean lightingWasEnabled = glIsEnabled(GL_LIGHTING);
    if (lightingWasEnabled) glDisable(GL_LIGHTING);

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.2f, 0.2f); glVertex3f(0.0f, 0.02f, 0.0f); glVertex3f(2.2f, 0.02f, 0.0f);
    glColor3f(0.2f, 1.0f, 0.2f); glVertex3f(0.0f, 0.02f, 0.0f); glVertex3f(0.0f, 2.2f, 0.0f);
    glColor3f(0.2f, 0.5f, 1.0f); glVertex3f(0.0f, 0.02f, 0.0f); glVertex3f(0.0f, 0.02f, 2.2f);
    glEnd();
    glLineWidth(1.0f);

    if (lightingWasEnabled) glEnable(GL_LIGHTING);
}

void Engine3D::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.applyView();
    mainLight.apply();

    drawTexturedFloor();
    drawCoordinateAxes();

    for (auto* obj : sceneObjects) {
        obj->draw();
    }

    window.display();
}

void Engine3D::run() {
    sf::Clock clock;
    while (isRunning && window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleEvents();
        update(deltaTime);
        render();
    }
    window.close();
}