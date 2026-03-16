#pragma once

#include <SFML/Graphics.hpp>

class SpriteRenderer 
{
public:
    SpriteRenderer() = default;
    SpriteRenderer(const sf::Sprite& sprite) : m_sprite(sprite) { }

    sf::Sprite& get_sprite() {
        return m_sprite;
    }

private:
    sf::Sprite m_sprite;
};