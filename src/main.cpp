#include <iostream>

#include <SFML/Graphics.hpp>

#include "scene.h"
#include "spatial_index.h"

class Movement
{
public:
    void update(Entity e, float dt)
    {
        e.mutate<Transform>([&](auto &transform) {
            transform.x += 64 * dt;
            transform.y += 64 * dt;
        });
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
    sf::RenderWindow window(sf::VideoMode({512, 512}), "Test");

    sf::Texture texture;
    bool _ = texture.loadFromFile("/var/home/finley/Documents/ProgrammingProjects/Test/charlieTheCapybaraAnimationSheet.png");

    sf::Sprite sprite(texture, { { 0, 64 }, { 64, 64 } });

    Scene scene;
    auto e = scene.create_entity();
    e.add<Transform>();
    e.add<Movement>();
    e.add<SpriteRenderer>(sprite);

    auto c = scene.create_entity();
    c.add<Transform>();
    c.add<Camera>();

    scene.start();

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        scene.update(clock.restart().asSeconds());

        window.clear();
        scene.render(window);
        window.display();
    }
}