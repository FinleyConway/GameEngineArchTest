#pragma once

#include <string>
#include <cstdint>

namespace test
{
    template<typename T>
    class Vector2
    {
    public:
        T x = 0;
        T y = 0;

    public:
        Vector2() = default;

        Vector2(T x, T y);

        template<typename U> operator Vector2<U>() const;

    public:
        std::string to_string() const;

        float lerp(Vector2 a, Vector2 b, float t) const;
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int32_t>;
    using Vector2u = Vector2<uint32_t>;

    template<typename T> Vector2<T> operator-(Vector2<T> right);
    template<typename T> Vector2<T>& operator+=(Vector2<T>& left, Vector2<T> right);
    template<typename T> Vector2<T>& operator-=(Vector2<T>& left, Vector2<T> right);
    template<typename T> Vector2<T> operator+(Vector2<T> left, Vector2<T> right);
    template<typename T> Vector2<T> operator-(Vector2<T> left, Vector2<T> right);
    template<typename T> Vector2<T> operator*(Vector2<T> left, T right);
    template<typename T> Vector2<T> operator*(T left, Vector2<T> right);
    template<typename T> Vector2<T>& operator*=(Vector2<T>& left, T right);
    template<typename T> Vector2<T> operator/(Vector2<T> left, T right);
    template<typename T> Vector2<T>& operator/=(Vector2<T>& left, T right);
    template<typename T> bool operator==(Vector2<T> left, Vector2<T> right);
    template<typename T> bool operator!=(Vector2<T> left, Vector2<T> right);
}

#include "math/vector2.inl"