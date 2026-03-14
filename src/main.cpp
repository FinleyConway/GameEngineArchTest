#include <iostream>
#include "scene.h"

class Transform 
{
public:
    float x() const { return m_x; }
    void x(float x) { m_x = x; }

    float y() const { return m_y; }
    void y(float y) { m_y = y; }

    std::string to_str() {
        return std::format("[x:{}, y:{}]", m_x, m_y);
    }

private:
    float m_x = 0;
    float m_y = 0;
};

class Movement
{
public:
    void update(Entity e, float dt) {
        auto& transform = e.get<Transform>();

        transform.x(transform.x() + 50 * dt);
        transform.y(transform.y() + 50 * dt);

        std::cout << transform.to_str() << std::endl;
    }
};

int main() {
    Scene scene;
    auto e = scene.create_entity();
    e.add<Transform>();
    e.add<Movement>();
    
    scene.start();

    while (true) {
        scene.update(0.016f);
    }
}