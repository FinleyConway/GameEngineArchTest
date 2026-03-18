#pragma once

#include "component_interfaces.h"
#include "sprite.h"

namespace test {
    class SpriteRenderer : public IRenderable
    {
    public:
        SpriteRenderer() = default;

        SpriteRenderer(const Sprite& sprite) : m_sprite(sprite) { }

        const Sprite& get_sprite() const {
            return m_sprite;
        }

    private:
        void draw(Vector2 position) const override {
            const Texture2D* texture = m_sprite.get_texture();
            Vector2 pivot = m_sprite.get_pivot();

            if (texture == nullptr) return;

            Vector2 draw_position = {
                .x = position.x - pivot.x,
                .y = position.y - pivot.y
            };

            DrawTextureRec(*texture, m_sprite.get_texture_rect(), draw_position, m_colour);
        }

    private:
        Sprite m_sprite;
        Color m_colour = WHITE;
    };
}