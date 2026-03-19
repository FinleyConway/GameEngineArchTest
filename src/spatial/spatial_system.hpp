#pragma once

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
            m_spatial_index.query(bounds, std::forward<Func>(func));
        }

    private:
        void on_sprite_added(entt::registry& registry, entt::entity entity);

        void on_sprite_removed(entt::registry&, entt::entity entity);

        void on_transform_change(entt::registry& registry, entt::entity entity);

        void update_entity(entt::registry& registry, entt::entity entity);

    private:
        SpatialIndex m_spatial_index;
    };
}