#include "rendering/render_system.hpp"

#include "rendering/renderer.hpp"
#include "spatial/spatial_system.hpp"
#include "scene/components/camera.hpp"
#include "scene/components/transform.hpp"
#include "scene/components/sprite_renderer.hpp"

namespace test
{
    RenderSystem::RenderSystem(Renderer& renderer, SpatialSystem& spatial) : m_renderer(renderer), m_spatial(spatial) {
    }

    void RenderSystem::render(entt::registry& registry) {
        auto view = registry.view<const Transform, const Camera>();

        if (view.begin() == view.end()) {
            m_renderer.draw_no_camera();
            return;
        }

        view.each([&](auto entity, const Transform& transform, const Camera& camera) {
            m_renderer.draw_in_view(transform, camera, [&](const FloatRect& bounds) {
                render_visible_entities(registry, bounds);
            });
        });
    }

    void RenderSystem::render_visible_entities(entt::registry& registry, const FloatRect& bounds)
    {
        m_spatial.query(bounds, [&](entt::entity entity) {
            const auto& transform = registry.get<Transform>(entity);

            render_sprite(registry, entity, transform, bounds);
        });
    }

    void RenderSystem::render_sprite(entt::registry& registry, entt::entity entity, const Transform& transform, const FloatRect& view_bounds) {
        if (auto* sprite_renderer = registry.try_get<SpriteRenderer>(entity)) {
            const auto& sprite = sprite_renderer->get_sprite();
            const auto& sprite_colour = sprite_renderer->get_colour();
            const auto sprite_bounds = sprite_renderer->get_global_bounds(transform);

            if (view_bounds.intersects(sprite_bounds)) {
                m_renderer.draw_sprite(transform.get_position(), sprite, sprite_colour);
            }
        }
    }
}