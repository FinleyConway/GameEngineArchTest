#include "core/application.hpp"

#include "test.h"

/*
REF: https://skypjack.github.io/entt/md_docs_2md_2entity.html
Ideas:
- Since mutate<T>() can send events to anything that uses on_update, components could listen to changes?
- Enemy mutates player health (take dmg) -> Player component could listen, has health changed? -> play hurt sound
- Will make it easier for e.g. rendering and only update the sprite position in data structure when transform changes
*/

class Movement : public test::Updatable
{
private:
    void update(test::Entity e, float dt) override {
        test::Vector2f direction = {0,0};

        if (test::Input::is_key_held(test::Key::W)) direction.y = -1;
        if (test::Input::is_key_held(test::Key::S)) direction.y = +1;
        if (test::Input::is_key_held(test::Key::A)) direction.x = -1;
        if (test::Input::is_key_held(test::Key::D)) direction.x = +1;

        e.write<test::Camera>([&](auto& camera) {
            if (test::Input::is_key_down(test::Key::Up)) camera.set_zoom(10);
            if (test::Input::is_key_down(test::Key::Down)) camera.set_zoom(1);
        });

        e.write<test::Transform>([&](auto& transform) {
            transform.translate(direction * 64.0f * dt);
        });
    }
};

int main()
{
    test::Application app({ test::Vector2i(500, 500), "test" });

    test::Texture red_square = test::Texture::create_rectangle(64, 64, RED);
    test::Texture white_circle = test::Texture::create_rectangle(64, 64, WHITE);

    test::Sprite red_sprite(red_square, { 0, 0, 64, 64 });
    test::Sprite white_sprite(white_circle, { 0, 0, 64, 64 });

    app.add_scene("game", [&](test::Scene& scene) {
        auto e = scene.create_entity();
        e.add<test::Transform>();
        e.add<Movement>();
        e.add<test::SpriteRenderer>(red_sprite, 1);
        e.add<test::Camera>();

        auto c = scene.create_entity();
        c.add<test::Transform>(0, 64);
        c.add<test::SpriteRenderer>(white_sprite);
    });

    app.set_current_scene("game");

    app.run();
}