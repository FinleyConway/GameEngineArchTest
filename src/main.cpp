#include <iostream>

#include <SFML/Graphics.hpp>

#include "scene.h"
#include "spatial_index.h"

class Transform
{
public:
    float x = 0;
    float y = 0;

    std::string to_str() const
    {
        return std::format("[x:{}, y:{}]", x, y);
    }
};

class Movement
{
public:
    void update(Entity e, float dt)
    {
        e.mutate<Transform>([&](auto &transform)
                            {
            transform.x += 50 * dt;
            transform.y += 50 * dt;

            std::cout << transform.to_str() << std::endl; });
    }
};

/*
REF: https://skypjack.github.io/entt/md_docs_2md_2entity.html
Ideas:
- Since mutate<T>() can send events to anything that uses on_update, components could listen to changes?
- Enemy mutates player health (take dmg) -> Player component could listen, has health changed? -> play hurt sound
- Will make it easier for e.g. rendering and only update the sprite position in data structure when transform changes
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "Test");

    Scene scene;
    auto e = scene.create_entity();
    e.add<Transform>();
    e.add<Movement>();

    scene.start();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        scene.update(0.016f);

        window.clear();
        window.display();
    }
}