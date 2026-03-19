#pragma once

#include <string>
#include <cstdint>

#include "math/vector2.hpp"

namespace test
{
    template<typename T>
    class Rect
    {
    public:
        T x = 0;
        T y = 0;
        T w = 0;
        T h = 0;

    public:
        Rect() = default;

        Rect(T x, T y, T w, T h);
        
        template<typename U> operator Rect<U>() const;

    public:
        std::string to_string() const;

        Vector2<T> get_position() const;

        Vector2<T> get_size() const;

        bool contains(T px, T py) const;

        bool intersects(const Rect<T>& other) const;
    };

    using FloatRect = Rect<float>;
    using IntRect = Rect<int32_t>;
    using UIntRect = Rect<uint32_t>;
}

#include "math/rect.inl"