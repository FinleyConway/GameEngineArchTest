#pragma once

#include "math/rect.hpp"
#include "math/vector2.hpp"
#include "rendering/texture.hpp"

namespace test 
{
    class Sprite
    {
    public:
        Sprite() = default;

        Sprite(const Texture& texture, const FloatRect& texture_rect);

        Sprite(const Texture& texture, const FloatRect& texture_rect, Vector2f pivot);

        const Texture& get_texture() const;

        Vector2f get_pivot() const;

        FloatRect get_texture_rect() const;

        FloatRect get_bounds() const;

    private:
        Vector2f generate_pivot(const FloatRect& texture_rect);

    private:
        FloatRect m_texture_rect;
        Vector2f m_pivot;
        Texture m_texture;
    };
}