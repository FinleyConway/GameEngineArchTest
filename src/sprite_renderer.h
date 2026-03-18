#pragma once

#include "sprite.h"

namespace test {
    class SpriteRenderer 
    {
    public:
        SpriteRenderer() = default;

        SpriteRenderer(const Sprite& sprite) : m_sprite(sprite) { }

        const Sprite& get_sprite() {
            return m_sprite;
        }

    private:
        Sprite m_sprite;
    };
}