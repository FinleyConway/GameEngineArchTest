#include "rendering/renderer.hpp"

#include "raylib.h"
#include "utils/to_rl.hpp"
#include "rendering/sprite.hpp"

namespace test 
{
    void Renderer::draw_no_camera() {
        const char* text = "No camera in the scene!";
        int font_size = 20;
        int text_width = ::MeasureText(text, font_size);

        ::DrawText(
            text,
            (::GetScreenWidth() - text_width) / 2,
            (::GetScreenHeight() - font_size) / 2,
            font_size,
            RED
        );
    }

    void Renderer::draw_sprite(Vector2f position, const Sprite& sprite, const Color& colour) {
        const ::Texture2D& handle = sprite.get_texture().get_handle();

        if (!::IsTextureValid(handle)) return; // maybe add a log here

        Vector2f pivot = sprite.get_pivot();
        Vector2f draw_position = position - pivot;

        ::DrawTextureRec(
            handle, 
            ToRl::from_float_rect(sprite.get_texture_rect()), 
            ToRl::from_vector2f(draw_position), 
            colour
        );
    }   

    Renderer::CameraView Renderer::compute_camera_view(const Transform& transform, const Camera& camera) const {
        float screen_w = ::GetScreenWidth();
        float screen_h = ::GetScreenHeight();

        float world_w = screen_w / camera.get_zoom();
        float world_h = screen_h / camera.get_zoom();

        ::Camera2D rl_camera {
            .offset = { 
                .x = screen_w / 2.0f, 
                .y = screen_h / 2.0f 
            },
            .target = ToRl::from_vector2f(transform.get_position()),
            .rotation = 0.0f, // no rotation support
            .zoom = camera.get_zoom()
        };

        FloatRect bounds(
            rl_camera.target.x - world_w / 2.0f,
            rl_camera.target.y - world_h / 2.0f,
            world_w,
            world_h
        );

        return CameraView(rl_camera, bounds);
    };
}