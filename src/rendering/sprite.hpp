#pragma once

#include <raylib.h>

#include "rendering/texture.hpp"
#include "math/rect.hpp"
#include "math/vector2.hpp"

namespace test 
{
    class Sprite
    {
    public:
        explicit Sprite() = default;

        Sprite(const Texture& texture, const FloatRect& texture_rect) 
            : m_texture_rect(texture_rect), m_pivot(generate_pivot(texture_rect)), m_texture(texture) { }

        Sprite(const Texture& texture, const FloatRect& texture_rect, Vector2f pivot) 
            : m_texture_rect(texture_rect), m_pivot(pivot), m_texture(texture) { }

        const Texture& get_texture() const {
            return m_texture;
        }

        Vector2f get_pivot() const {
            return m_pivot;
        }

        FloatRect get_texture_rect() const {
            return m_texture_rect;
        }

        FloatRect get_bounds() const {
            return test::FloatRect(
                -m_pivot.x,
                -m_pivot.y,
                m_texture_rect.w,
                m_texture_rect.h
            );
        }

    private:
        Vector2f generate_pivot(const FloatRect& texture_rect) {
            return Vector2f(
                texture_rect.w / 2.0f,
                texture_rect.h / 2.0f
            );
        }

    private:
        FloatRect m_texture_rect;
        Vector2f m_pivot;
        Texture m_texture;
    };
}