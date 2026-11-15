#include "Engine3D.hpp"

int main() {
    Engine3D engine(1024, 768, "3D Game Engine Framework (Labs 7-11)");
    engine.init();
    engine.run();
    return 0;
}