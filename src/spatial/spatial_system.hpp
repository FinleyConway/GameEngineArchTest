#pragma once

#include <entt/entt.hpp>

#include "entt/entity/fwd.hpp"
#include "spatial/spatial_index.hpp"
#include "math/rect.hpp"

namespace test 
{
    class SpatialSystem 
    {
    public:
        explicit SpatialSystem(entt::registry& registry);

        template<typename Func>
        void query(const FloatRect& bounds, Func&& func) {
            for (auto entity : m_deferred_entities) {
                update_entity(entity);
            }

            m_deferred_entities.clear();
            m_spatial_index.query(bounds, std::forward<Func>(func));
        }

    private:
        void on_sprite_added(entt::registry&, entt::entity entity);

        void on_sprite_removed(entt::registry&, entt::entity entity);

        void on_transform_change(entt::registry&, entt::entity entity);

        void update_entity(entt::entity entity);
        
        void update_sprite(entt::entity entity);

    private:
        entt::registry& m_registry;
        SpatialIndex m_spatial_index;
        entt::sparse_set m_deferred_entities;
    };
}