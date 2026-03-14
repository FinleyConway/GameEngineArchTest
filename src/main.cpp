#include <iostream>
#include "scene.h"

struct Trasform {
    float x = 10, y = 50;

    void update(Entity entity, float dt) {
        std::cout << to_str() << std::endl;
    }

    std::string to_str() {
        return std::format("[x:{}, y:{}]", x, y);
    }
};

int main() {
    Scene scene;
    scene.create_entity().add<Trasform>();
    
    while (true) {
        scene.update(0.016f);
    }
}