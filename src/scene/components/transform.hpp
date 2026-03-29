#pragma once

#include "math/vector2.hpp"

namespace mz 
{
    class Transform
    {
    public:
        Transform() = default;

        Transform(float x, float y) : m_position(x, y) { }

        explicit Transform(Vector2f position) : m_position(position) { }

    public:
        Vector2f get_position() const {
            return m_position;
        }

        void set_position(Vector2f position) {
            m_position = position;
        }

        void translate(Vector2f position) {
            m_position += position;
        }

    private:
        Vector2f m_position;
    };
}