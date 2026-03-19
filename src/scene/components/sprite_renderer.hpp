#pragma once

#include <raylib.h>

#include "scene/interfaces/renderable.hpp"
#include "rendering/sprite.hpp"
#include "math/vector2.hpp"

#include "utils/to_rl.hpp"

namespace test 
{
    class SpriteRenderer : public Renderable
    {
    public:
        SpriteRenderer() = default;

        SpriteRenderer(const Sprite& sprite) : m_sprite(sprite) { }

        const Sprite& get_sprite() const {
            return m_sprite;
        }

    private:
        void draw(Vector2f position) const override {
            if (!m_sprite.get_texture().is_valid()) return; // maybe add a log here

            const Texture2D& handle = m_sprite.get_texture().get_handle();
            Vector2f pivot = m_sprite.get_pivot();
            Vector2f draw_position = {
                position.x - pivot.x,
                position.y - pivot.y
            };

            DrawTextureRec(
                handle, 
                ToRl::from_float_rect(m_sprite.get_texture_rect()), 
                ToRl::from_vector2f(draw_position), 
                m_colour
            );
        }

    private:
        Sprite m_sprite;
        Color m_colour = WHITE;
    };
}