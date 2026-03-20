#pragma once

#include <raylib.h>

#include "scene/components/transform.hpp"
#include "scene/components/camera.hpp"
#include "math/rect.hpp"

namespace test 
{
    class Sprite;

    class Renderer
    {
    private:
        struct CameraView 
        {
            ::Camera2D rl_camera;
            FloatRect bounds;
        };

    public:
        template<typename Fn>
        void draw_in_window(const Color& clear_colour, Fn&& fn) {
            ::BeginDrawing();
            ::ClearBackground(clear_colour);

            fn();

            ::EndDrawing();
        }   

        template<typename Fn>
        void draw_in_view(const Transform& transform, const Camera& camera, Fn&& fn) {
            CameraView view = compute_camera_view(transform, camera);

            ::BeginMode2D(view.rl_camera);

            fn(view.bounds);

            ::EndMode2D();
        }

        void draw_no_camera();

        void draw_sprite(Vector2f position, const Sprite& sprite, const Color& colour);

    private:
        CameraView compute_camera_view(const Transform& transform, const Camera& camera) const;
    };
}