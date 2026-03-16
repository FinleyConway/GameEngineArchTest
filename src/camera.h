#pragma once

#include <SFML/Graphics.hpp>

class Camera 
{
public:
    Camera() = default;
    Camera(const sf::View& view) : m_view(view) {}

    sf::View& get_view() {
        return m_view;
    }

private:
    sf::View m_view;
};