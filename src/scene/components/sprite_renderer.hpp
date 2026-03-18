#pragma once

#include <raylib.h>

#include "scene/interfaces/renderable.hpp"
#include "rendering/sprite.hpp"

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
        void draw(Vector2 position) const override {
            if (!m_sprite.get_texture().is_valid()) return; // maybe add a log here

            const Texture2D& handle = m_sprite.get_texture().get_handle();
            Vector2 pivot = m_sprite.get_pivot();
            Vector2 draw_position = {
                .x = position.x - pivot.x,
                .y = position.y - pivot.y
            };

            DrawTextureRec(handle, m_sprite.get_texture_rect(), draw_position, m_colour);
        }

    private:
        Sprite m_sprite;
        Color m_colour = WHITE;
    };
}