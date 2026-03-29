#include "rendering/renderer.hpp"

#include <raylib.h>

#include "scene/components/camera.hpp"
#include "scene/components/transform.hpp"
#include "rendering/sprite.hpp"
#include "utils/to_rl.hpp"

namespace mz 
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

    ::Camera2D Renderer::create_rl_camera(Vector2f position, float zoom) {
        Vector2f world_size = get_world_size(zoom);

        return {
            .offset = { 
                .x = world_size.x / 2.0f, 
                .y = world_size.y / 2.0f 
            },
            .target = ToRl::from_vector2f(position),
            .rotation = 0.0f, // no rotation support
            .zoom = zoom
        };
    }

    Vector2f Renderer::get_world_size(float zoom) {
        float screen_w = ::GetScreenWidth();
        float screen_h = ::GetScreenHeight();

        return { screen_w / zoom, screen_h / zoom };
    }

    Renderer::CameraView Renderer::compute_camera_view(const Transform& transform, const Camera& camera) const {
        Vector2f world_size = get_world_size(camera.get_zoom());
        ::Camera2D rl_camera = create_rl_camera(transform.get_position(), camera.get_zoom());

        FloatRect bounds(
            rl_camera.target.x - world_size.x / 2.0f,
            rl_camera.target.y - world_size.y / 2.0f,
            world_size.x,
            world_size.y
        );

        return CameraView(rl_camera, bounds);
    };
}