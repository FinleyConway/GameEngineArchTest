#pragma once

#include "scene/components/transform.hpp"
#include "rendering/sprite.hpp"
#include "math/vector2.hpp"

namespace test 
{
    class SpriteRenderer
    {
    public:
        SpriteRenderer() = default;

        SpriteRenderer(const Sprite& sprite) : m_sprite(sprite) { }

        FloatRect get_global_bounds(const Transform& transform) const {
            FloatRect local = m_sprite.get_bounds();
            Vector2f position = transform.get_position();

            return FloatRect(
                position.x + local.x,
                position.y + local.y,
                local.w,
                local.h
            );
        }

        const Color& get_colour() const {
            return m_colour;
        }

        const Sprite& get_sprite() const {
            return m_sprite;
        }

    private:
        Sprite m_sprite;
        Color m_colour = WHITE;
    };
}