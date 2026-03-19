#include "rendering/sprite.hpp"

namespace test
{
    Sprite::Sprite(const Texture& texture, const FloatRect& texture_rect) 
        : m_texture_rect(texture_rect), m_pivot(generate_pivot(texture_rect)), m_texture(texture) { 
    }

    Sprite::Sprite(const Texture& texture, const FloatRect& texture_rect, Vector2f pivot) 
        : m_texture_rect(texture_rect), m_pivot(pivot), m_texture(texture) { 
    }

    const Texture& Sprite::get_texture() const {
        return m_texture;
    }

    Vector2f Sprite::get_pivot() const {
        return m_pivot;
    }

    FloatRect Sprite::get_texture_rect() const {
        return m_texture_rect;
    }

    FloatRect Sprite::get_bounds() const {
        return test::FloatRect(
            -m_pivot.x,
            -m_pivot.y,
            m_texture_rect.w,
            m_texture_rect.h
        );
    }

    Vector2f Sprite::generate_pivot(const FloatRect& texture_rect) {
        return Vector2f(
            texture_rect.w / 2.0f,
            texture_rect.h / 2.0f
        );
    }
}