#pragma once

#include <entt/entt.hpp>

#include "scene/components/camera.hpp"
#include "scene/components/transform.hpp"
#include "scene/components/sprite_renderer.hpp"

#include "spatial/spatial_system.hpp"
#include "math/rect.hpp"

#include "utils/to_rl.hpp"

namespace test
{
    struct CameraView {
        Camera2D rl_camera;
        FloatRect bounds;
    };

    class RenderSystem 
    {
    public:
        explicit RenderSystem(SpatialSystem& spatial) : m_spatial(spatial) {}

        void render(entt::registry& registry) {
            auto view = registry.view<Transform, Camera>();

            if (view.begin() == view.end()) {
                draw_no_camera();
                return;
            }

            view.each([&](auto entity, Transform& transform, Camera& camera) {
                render_camera(registry, transform, camera);
            });
        }

    private:
        void render_camera(entt::registry& registry, const Transform& transform, const Camera& camera)
        {
            CameraView view = compute_camera_view(transform, camera);

            BeginMode2D(view.rl_camera);

            m_spatial.query(view.bounds, [&](entt::entity entity) {
                const auto& t = registry.get<Transform>(entity);

                if (auto* sr = registry.try_get<SpriteRenderer>(entity)) {
                    const auto& renderable = static_cast<const Renderable&>(*sr);

                    renderable.draw(t.get_position());
                }
            });

            EndMode2D();
        }

        CameraView compute_camera_view(const Transform& transform, const Camera& camera) {
            float screen_w = GetScreenWidth();
            float screen_h = GetScreenHeight();

            float world_w = screen_w / camera.get_zoom();
            float world_h = screen_h / camera.get_zoom();

            Camera2D rl_camera {
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
        }

        void draw_no_camera() {
            const char* text = "No camera in the scene!";
            int font_size = 20;

            int text_width = MeasureText(text, font_size);

            DrawText(
                text,
                (GetScreenWidth() - text_width) / 2,
                (GetScreenHeight() - font_size) / 2,
                font_size,
                RED
            );
        }

    private:
        SpatialSystem& m_spatial;
    };
}