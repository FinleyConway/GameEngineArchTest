#pragma once

#include "raylib.h"

namespace test {
    class Sprite
    {
    public:
        explicit Sprite() = default;

        Sprite(const Texture2D* texture, const Rectangle& texture_rect) 
            : m_texture_rect(texture_rect), m_pivot(generate_pivot(texture_rect)), m_texture(texture) { }

        Sprite(const Texture2D* texture, const Rectangle& texture_rect, Vector2 pivot) 
            : m_texture_rect(texture_rect), m_pivot(pivot), m_texture(texture) { }

        Rectangle get_bounds(Vector2 position) const {
            return {
                .x = position.x - m_pivot.x,
                .y = position.y - m_pivot.y,
                .width  = m_texture_rect.width,
                .height = m_texture_rect.height
            };
        }

        void draw(Vector2 position, Color colour) const {
            if (m_texture == nullptr) return;

            Vector2 draw_position = {
                .x = position.x - m_pivot.x,
                .y = position.y - m_pivot.y
            };

            DrawTextureRec(*m_texture, m_texture_rect, draw_position, colour);
        }

    private:
        Vector2 generate_pivot(const Rectangle& texture_rect) {
            return {
                .x = texture_rect.width / 2.0f,
                .y = texture_rect.height / 2.0f
            };
        }

    private:
        Rectangle m_texture_rect;
        Vector2 m_pivot;
        const Texture2D* m_texture = nullptr;
    };
}