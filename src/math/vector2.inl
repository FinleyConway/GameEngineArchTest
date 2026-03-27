#pragma once

#include <algorithm>
#include <format>
#include <cmath>

#include "math/vector2.hpp"

namespace test
{
    template<typename T>
    Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

    template <typename T>
    template <typename U>
    Vector2<T>::operator Vector2<U>() const {
        return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
    }

    template<typename T>
    std::string Vector2<T>::to_string() const {
        return std::format("({}, {})", x, y);
    }

    template<typename T>
    float Vector2<T>::lerp(Vector2<T> a, Vector2<T> b, float t) const {
        t = std::clamp(t, 0.0f, 1.0f);

        T x = std::lerp(a.x, b.x, t);
        T y = std::lerp(a.y, b.y, t);

        return Vector2<T>(x, y);
    }

    template <typename T>
    Vector2<T> operator-(Vector2<T> right) {
        return Vector2<T>(-right.x, -right.y);
    }

    template <typename T>
    Vector2<T>& operator+=(Vector2<T>& left, Vector2<T> right) {
        left.x += right.x;
        left.y += right.y;

        return left;
    }

    template <typename T>
    Vector2<T>& operator-=(Vector2<T>& left, Vector2<T> right) {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }

    template <typename T>
    Vector2<T> operator+(Vector2<T> left, Vector2<T> right) {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }

    template <typename T>
    Vector2<T> operator-(Vector2<T> left, Vector2<T> right) {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }

    template <typename T>
    Vector2<T> operator*(Vector2<T> left, T right) {
        return Vector2<T>(left.x * right, left.y * right);
    }

    template <typename T>
    Vector2<T> operator*(T left, Vector2<T> right) {
        return Vector2<T>(right.x * left, right.y * left);
    }

    template <typename T>
    Vector2<T>& operator*=(Vector2<T>& left, T right) {
        left.x *= right;
        left.y *= right;

        return left;
    }

    template <typename T>
    Vector2<T> operator/(Vector2<T> left, T right) {
        assert(right != 0 && "Vector2::operator/ cannot divide by 0");
        return Vector2<T>(left.x / right, left.y / right);
    }

    template <typename T>
    Vector2<T>& operator/=(Vector2<T>& left, T right) {
        assert(right != 0 && "Vector2::operator/= cannot divide by 0");
        left.x /= right;
        left.y /= right;

        return left;
    }

    template <typename T>
    bool operator==(Vector2<T> left, Vector2<T> right) {
        return (left.x == right.x) && (left.y == right.y);
    }

    template <typename T>
    bool operator!=(Vector2<T> left, Vector2<T> right) {
        return !(left == right);
    }
}