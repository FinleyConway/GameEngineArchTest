#pragma once

#include <string>
#include <cstdint>

namespace mz
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

        Vector2<T> lerp(Vector2 to, float t) const;

    public:
        struct Hash
        {
            size_t operator()(const Vector2& v) const {
                // https://stackoverflow.com/a/55083395
                size_t hash = std::hash<int32_t>()(v.x);

                hash <<= sizeof(size_t) * 4;
                hash ^= std::hash<int32_t>()(v.y);

                return std::hash<size_t>()(hash);
            }
        };
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