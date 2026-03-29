#include "core/application.hpp"
#include "maize.h"

#include "zgame_test/mine_cart.hpp"
#include "zgame_test/rail_map.hpp"
#include "zgame_test/rail_placer.hpp"

int main()
{
    mz::Application app({ mz::Vector2i(500, 500), "test" });

    mz::Texture red_square = mz::Texture::create_rectangle(32, 32, RED);
    mz::Sprite red_sprite(red_square, { 0, 0, 32, 32 });

    app.add_scene("game", [&](mz::Scene& scene) {
        auto camera = scene.create_entity();
        camera.add<mz::Camera>();
        camera.add_tag<mz::MainCameraTag>();

        auto rail_map = scene.create_entity();
        rail_map.add<RailMap>();
        rail_map.add<RailPlacer>();

        auto mine_cart = scene.create_entity();
        mine_cart.add<mz::SpriteRenderer>(red_sprite);
        mine_cart.add<MineCart>();
    });

    app.set_current_scene("game");
    app.run();
}