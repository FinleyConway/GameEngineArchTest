#pragma once

#include <entt/entt.hpp>

#include "math/rect.hpp"

namespace test
{   
    class SpatialSystem;
    class Renderer;
    class Transform;
    class Camera;

    class RenderSystem 
    {
    struct RenderEntity;

    public:
        RenderSystem(Renderer& renderer, SpatialSystem& spatial);

        void render(entt::registry& registry);

    private:
        void render_visible_entities(entt::registry& registry, const FloatRect& bounds);

        static bool sort_entities(const RenderEntity& a, const RenderEntity& b);

        void render_sprite(entt::registry& registry, entt::entity entity, const Transform& transform, const FloatRect& view_bounds);

    private:
        struct RenderEntity 
        {
            entt::entity entity;
            int32_t sort_order = 0;
        };

    private:
        Renderer& m_renderer;
        SpatialSystem& m_spatial;
        std::vector<RenderEntity> m_queried_entities;
    };
}