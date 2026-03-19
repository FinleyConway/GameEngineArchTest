#pragma once

#include "math/rect.hpp"

namespace test
{
    template<typename T>
    Rect<T>::Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}

    template <typename T>
    template <typename U>
    Rect<T>::operator Rect<U>() const {
        return Rect<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(w), static_cast<U>(h));
    }

    template<typename T>
    std::string Rect<T>::to_string() const {
        return std::format("({}, {}, {}, {})", x, y, w, h);
    }

    template<typename T>
    Vector2<T> Rect<T>::get_position() const {
        return Vector2<T>(x, y);
    }

    template<typename T>
    Vector2<T> Rect<T>::get_size() const {
        return Vector2<T>(w, h);
    }
}