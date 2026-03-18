#pragma once

#include <raylib.h>

#include "spatial/spatial_index.hpp"
#include "scene/components/sprite_renderer.hpp"
#include "scene/components/transform.hpp"

namespace test 
{
    class SpatialSystem 
    {
    public:
        SpatialSystem(entt::registry& registry) : m_spatial_index(32.0f) {
            registry.on_update<Transform>()
                .connect<&SpatialSystem::on_transform_change>(this);

            registry.on_construct<SpriteRenderer>()
                .connect<&SpatialSystem::on_sprite_added>(this);

            registry.on_destroy<SpriteRenderer>()
                .connect<&SpatialSystem::on_sprite_removed>(this);
        }

        template<typename Func>
        void query(const AABB& bounds, Func&& func) {
            m_spatial_index.query(bounds, std::forward<Func>(func));
        }

    private:
        void on_sprite_added(entt::registry& registry, entt::entity entity) {
            update_entity(registry, entity);
        }

        void on_sprite_removed(entt::registry&, entt::entity entity) {
            m_spatial_index.remove(entity);
        }

        void on_transform_change(entt::registry& registry, entt::entity entity) {
            if (registry.all_of<SpriteRenderer>(entity)) {
                update_entity(registry, entity);
            }
        }

        void update_entity(entt::registry& registry, entt::entity entity) {
            const auto& transform = registry.get<Transform>(entity);
            const auto& sprite = registry.get<SpriteRenderer>(entity);

            Rectangle bounds = sprite.get_sprite().get_bounds(transform.get_position());

            m_spatial_index.remove(entity);
            m_spatial_index.insert(entity, {
                bounds.x, bounds.y, bounds.width, bounds.height
            });
        }

    private:
        SpatialIndex m_spatial_index;
    };
}