#pragma once

#include <entt/entt.hpp>

#include "camera.h"
#include "transform.h"
#include "sprite_renderer.h"

#include "spatial_index.h"

namespace test {
    class Render 
    {
    public:
        Render(entt::registry& registry) : m_spatial_index(32.0f) {
            registry.on_update<Transform>().connect<&Render::on_transform_change>(this);
        }

        void render_entities(entt::registry& registry) {
            auto view = registry.view<Transform, Camera>();

            if (view.begin() == view.end()) {
                return draw_no_camera_info();
            }

            view.each([&](auto entity, Transform& transform, Camera& camera) {
                render_entity_in_camera(registry, transform, camera);
            });
        }

        void on_renderer_add(entt::registry& registery, entt::entity entity) {
            const auto& transform = registery.get<Transform>(entity);
            const auto& sprite_renderer = registery.get<SpriteRenderer>(entity);

            Rectangle bounds = sprite_renderer.get_sprite().get_bounds(transform.get_position());

            m_spatial_index.insert(entity, {
                .x = bounds.x,
                .y = bounds.y,
                .w = bounds.width,
                .h = bounds.height,
            });
        }

    private:
        void draw_no_camera_info() {
            const char* text = "No camera in the scene!";
            int font_size = 20;

            int text_width = MeasureText(text, font_size);

            int x = (GetScreenWidth() - text_width) / 2;
            int y = (GetScreenHeight() - font_size) / 2;

            DrawText(text, x, y, font_size, RED);
        }

        void render_entity_in_camera(entt::registry& registery, const Transform& transform, const Camera& camera) {
            float screen_width = GetScreenWidth();
            float screen_height = GetScreenHeight(); // maybe temp

            float world_width  = screen_width  / camera.get_zoom();
            float world_height = screen_height / camera.get_zoom();

            Camera2D rlCamera;
            rlCamera.target = transform.get_position();              
            rlCamera.offset = { screen_width / 2.0f, screen_height / 2.0f }; 
            rlCamera.rotation = 0.0f; // no rotation support
            rlCamera.zoom = camera.get_zoom();

            AABB bounds = {
                .x = rlCamera.target.x - world_width  / 2.0f,
                .y = rlCamera.target.y - world_height / 2.0f,
                .w = world_width,
                .h = world_height
            };

            BeginMode2D(rlCamera);

            m_spatial_index.query(bounds, [&](entt::entity entity) {
                const auto& sprite_transform = registery.get<Transform>(entity);

                if (const auto* sprite_renderer = registery.try_get<SpriteRenderer>(entity)) { // perhaps add a intersect check
                    const auto& renderable = static_cast<const IRenderable&>(*sprite_renderer);

                    renderable.draw(sprite_transform.get_position());
                }
            });

            EndMode2D();
        }

        // i should batch these to happen at once rather then on change since transform will change alot before drawing phase
        void on_transform_change(entt::registry& registery, entt::entity entity) { 
            if (const auto* sprite_renderer = registery.try_get<SpriteRenderer>(entity)) {
                const auto& transform = registery.get<Transform>(entity);

                Rectangle bounds = sprite_renderer->get_sprite().get_bounds(transform.get_position());

                m_spatial_index.remove(entity);
                m_spatial_index.insert(entity, {
                    .x = bounds.x,
                    .y = bounds.y,
                    .w = bounds.width,
                    .h = bounds.height,
                });
            }
        }

    private:
        SpatialIndex m_spatial_index;
    };
}