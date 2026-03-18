#pragma once

#include <string>

#include <raylib.h>

namespace test {
    class Transform
    {
    public:
        float x = 0;
        float y = 0;

        explicit Transform() = default;
        Transform(float x, float y) : x(x), y(y) { }

        Vector2 get_position() const {
            return Vector2(x, y);
        }

        std::string to_str() const {
            return std::format("[x:{}, y:{}]", x, y);
        }
    };
}