#include <iostream>
#include "scene.h"

class Trasform 
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

class Movement : public IUpdatable
{
protected:
    void update(Entity e, float dt) override {
        auto& transform = e.get<Trasform>();

        transform.x(transform.x() + 50 * dt);
        transform.y(transform.y() + 50 * dt);

        std::cout << transform.to_str() << std::endl;
    }
};

int main() {
    Scene scene;
    auto e = scene.create_entity();
    e.add<Trasform>();
    e.add<Movement>();
    
    scene.start();

    while (true) {
        scene.update(0.016f);
    }
}