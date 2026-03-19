#pragma once

#include <raylib.h>
#include <entt/entt.hpp>

#include "math/rect.hpp"

namespace test
{   
    class SpatialSystem;
    class Transform;
    class Camera;

    class RenderSystem 
    {
    public:
        explicit RenderSystem(SpatialSystem& spatial);

        void render(entt::registry& registry);

    private:
        struct CameraView 
        {
            Camera2D rl_camera;
            FloatRect bounds;
        };

    private:
        void render_camera(entt::registry& registry, const Transform& camera_transform, const Camera& camera);

        CameraView compute_camera_view(const Transform& transform, const Camera& camera);

        void render_sprite(entt::registry& registry, entt::entity entity, const Transform& transform, const FloatRect& view_bounds);

        void draw_no_camera();

    private:
        SpatialSystem& m_spatial;
    };
}