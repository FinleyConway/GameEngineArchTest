#pragma once

#include <raylib.h>

#include "scene/entity.hpp"
#include "scene/components/transform.hpp"
#include "rendering/renderer.hpp"
#include "math/vector2.hpp"
#include "utils/to_rl.hpp"

namespace test 
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

        Vector2f get_screen_to_world(Entity e, Vector2f screen_position) const {
            Vector2f position;

            e.read<Transform>([&](auto& t) {
                position = t.get_position();
            });

            ::Camera2D rl_camera = Renderer::create_rl_camera(position, m_zoom);
            ::Vector2 world_position = ::GetScreenToWorld2D(ToRl::from_vector2f(screen_position), rl_camera);

            return Vector2f(world_position.x, world_position.y);
        }

    private:
        float m_zoom = 1;
        ::Color m_background_colour = BLACK;
    };
}