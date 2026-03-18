#pragma once

#include <raylib.h>

namespace test {
    class Sprite
    {
    public:
        explicit Sprite() = default;

        Sprite(const Texture2D* texture, const Rectangle& texture_rect) 
            : m_texture_rect(texture_rect), m_pivot(generate_pivot(texture_rect)), m_texture(texture) { }

        Sprite(const Texture2D* texture, const Rectangle& texture_rect, Vector2 pivot) 
            : m_texture_rect(texture_rect), m_pivot(pivot), m_texture(texture) { }

        const Texture2D* get_texture() const {
            return m_texture;
        }

        Vector2 get_pivot() const {
            return m_pivot;
        }

        Rectangle get_texture_rect() const {
            return m_texture_rect;
        }

        Rectangle get_bounds(Vector2 position) const {
            return {
                .x = position.x - m_pivot.x,
                .y = position.y - m_pivot.y,
                .width  = m_texture_rect.width,
                .height = m_texture_rect.height
            };
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