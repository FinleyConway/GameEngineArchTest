#include "spatial/spatial_system.hpp"

#include "scene/components/sprite_renderer.hpp"
#include "scene/components/transform.hpp"

namespace test
{
    SpatialSystem::SpatialSystem(entt::registry& registry) : m_registry(registry), m_spatial_index(32.0f) {
        registry.on_update<Transform>()
            .connect<&SpatialSystem::on_transform_change>(this);

        registry.on_construct<SpriteRenderer>()
            .connect<&SpatialSystem::on_sprite_added>(this);

        registry.on_destroy<SpriteRenderer>()
            .connect<&SpatialSystem::on_sprite_removed>(this);
    }

    void SpatialSystem::on_sprite_added(entt::registry&, entt::entity entity) {
        update_sprite(entity);
    }

    void SpatialSystem::on_sprite_removed(entt::registry&, entt::entity entity) {
        m_spatial_index.remove(entity);
    }

    void SpatialSystem::on_transform_change(entt::registry&, entt::entity entity) {
        if  (!m_deferred_entities.contains(entity)) {
            m_deferred_entities.push(entity);
        }
    }

    void SpatialSystem::update_entity(entt::entity entity) {
        if (m_registry.all_of<SpriteRenderer>(entity)) {
            update_sprite(entity);
        }
    }

    void SpatialSystem::update_sprite(entt::entity entity) {
        const auto& transform = m_registry.get<Transform>(entity);
        const auto& sprite = m_registry.get<SpriteRenderer>(entity);

        FloatRect bounds = sprite.get_global_bounds(transform);

        m_spatial_index.remove(entity);
        m_spatial_index.insert(entity, bounds);
    }
}