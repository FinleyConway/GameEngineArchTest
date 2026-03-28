#include "core/application.hpp"
#include "test.h"

#include "zgame_test/mine_cart.hpp"
#include "zgame_test/rail_map.hpp"

int main()
{
    test::Application app({ test::Vector2i(500, 500), "test" });

    test::Texture red_square = test::Texture::create_rectangle(32, 32, RED);
    test::Sprite red_sprite(red_square, { 0, 0, 32, 32 });

    app.add_scene("game", [&](test::Scene& scene) {
        auto camera = scene.create_entity();
        camera.add<test::Transform>();
        camera.add<test::Camera>();

        auto rail_map = scene.create_entity();
        rail_map.add<test::Transform>();
        rail_map.add<RailMap>();

        auto mine_cart = scene.create_entity();
        mine_cart.add<test::Transform>(0, 64);
        mine_cart.add<test::SpriteRenderer>(red_sprite);
        mine_cart.add<MineCart>();
    });

    app.set_current_scene("game");
    app.run();
}