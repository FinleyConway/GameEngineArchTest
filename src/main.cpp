#include <iostream>

#include <raylib.h>

#include "scene/scene.hpp"
#include "scene/interfaces/updatable.hpp"
#include "scene/components/transform.hpp"
#include "scene/components/sprite_renderer.hpp"
#include "scene/components/camera.hpp"

class Movement : public test::Updatable
{
private:
    void update(test::Entity e, float dt) override {
        Vector2 direction = {0,0};

        if (IsKeyDown(KEY_W)) direction.y = -1;
        if (IsKeyDown(KEY_S)) direction.y = +1;
        if (IsKeyDown(KEY_A)) direction.x = -1;
        if (IsKeyDown(KEY_D)) direction.x = +1;

        e.mutate<test::Camera>([&](auto& camera) {
            if (IsKeyDown(KEY_UP)) camera.set_zoom(10);
            if (IsKeyDown(KEY_DOWN)) camera.set_zoom(1);
        });

        e.mutate<test::Transform>([&](auto& transform) {
            transform.x += direction.x * 64 * dt;
            transform.y += direction.y * 64 * dt;
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
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(500, 500, "window");
    SetTargetFPS(60);

    Image red_img = GenImageColor(64, 64, RED); 
    Texture2D red_texture = LoadTextureFromImage(red_img);
    UnloadImage(red_img);

    Image img = GenImageColor(64, 64, WHITE); 
    Texture2D white_texture = LoadTextureFromImage(img);
    UnloadImage(img);

    test::Sprite red_sprite(&red_texture, { 0, 64, 64, 64 });
    test::Sprite white_sprite(&white_texture, { 0, 64, 64, 64 });

    test::Scene scene;
    auto e = scene.create_entity();
    e.add<test::Transform>();
    e.add<Movement>();
    e.add<test::SpriteRenderer>(red_sprite);
    e.add<test::Camera>();

    auto c = scene.create_entity();
    c.add<test::Transform>(0, 64);
    c.add<test::SpriteRenderer>(white_sprite);

    scene.start();

    while (!WindowShouldClose()) {
        scene.update(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        scene.render();
        EndDrawing();
    }

    UnloadTexture(red_texture);
    UnloadTexture(white_texture);
    CloseWindow();
}