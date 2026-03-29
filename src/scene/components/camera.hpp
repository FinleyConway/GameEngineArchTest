#pragma once

#include <raylib.h>

#include "scene/components/transform.hpp"
#include "scene/tags/main_camera_tag.hpp"
#include "rendering/renderer.hpp"
#include "math/vector2.hpp"
#include "scene/entity.hpp"
#include "utils/to_rl.hpp"

namespace mz 
{
    class Camera 
    {
    public:
        float get_zoom() const {
            return m_zoom;
        }

        void set_zoom(float zoom) {
            if (zoom <= 0.0f) return;

            m_zoom = zoom;
        }

        void set_background_colour(::Color colour) {
            m_background_colour = colour;
        }

        ::Color get_background_colour() const {
            return m_background_colour;
        }

    public:
        static Entity get_main(Entity e) {
            e.get_entities_with<MainCameraTag>([](Entity e) {
                return e;
            }); 

            return Entity();
        }

        static Vector2f get_screen_to_world(Entity camera_entity, Vector2f screen_position) {
            if (!camera_entity.has<Camera>()) return Vector2f(0, 0); // add log?

            const auto* t = camera_entity.read<Transform>();
            const auto* c = camera_entity.read<Camera>();

            ::Camera2D rl_camera = Renderer::create_rl_camera(t->get_position(), c->get_zoom());
            ::Vector2 world_position = ::GetScreenToWorld2D(ToRl::from_vector2f(screen_position), rl_camera);

            return Vector2f(world_position.x, world_position.y);
        }

    private:
        float m_zoom = 1;
        ::Color m_background_colour = BLACK;
    };
}