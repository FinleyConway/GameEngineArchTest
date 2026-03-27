#pragma once

#include <expected>
#include <cstdint>
#include <vector>

#include "math/vector2.hpp"

template<typename T>
class Grid 
{
public:
    enum class Error {
        None,
        IsEmpty,
        OutOfBounds
    };

public:
    Grid() = default;

    Grid(int32_t width, int32_t height) :
        m_data(width * height), m_width(width), m_height(height) {
    }

    explicit Grid(test::Vector2i size) :
        m_data(size.x * size.y), m_width(size.x), m_height(size.y) {
    }

    int32_t get_width() const {
        return m_width;
    }

    int32_t get_height() const {
        return m_height;
    }

    bool is_within(int32_t x, int32_t y) const {
        return x >= 0 && y >= 0 && x < m_width && y < m_height;
    }

    bool is_within(test::Vector2i position) const {
        return is_within(position.x, position.y);
    }

    std::expected<T&, Error> get(int32_t x, int32_t y) {
        if (m_data.empty()) return std::unexpected(Error::IsEmpty);
        if (!is_within(x, y)) return std::unexpected(Error::OutOfBounds);

        return m_data[get_index(x, y)];
    }

    std::expected<T&, Error> get(test::Vector2i position) {
        return get(position.x, position.y);
    }

    std::expected<const T&, Error> get(int32_t x, int32_t y) const {
        if (m_data.empty()) return std::unexpected(Error::IsEmpty);
        if (!is_within(x, y)) return std::unexpected(Error::OutOfBounds);

        return m_data[get_index(x, y)];
    }

    std::expected<const T&, Error> get(test::Vector2i position) const {
        return get(position.x, position.y);
    }

    Error set(int32_t x, int32_t y, const T& value) {
        if (m_data.empty()) return Error::IsEmpty;
        if (!is_within(x, y)) return Error::OutOfBounds;

        m_data[get_index(x, y)] = value;

        return Error::None;
    }

    Error set(test::Vector2i position, const T& value) {
        return set(position.x, position.y, value);
    }

private:
    int32_t get_index(int32_t x, int32_t y) const {
        return y * m_width + x;
    }

private:
    std::vector<T> m_data;
    int32_t m_width = 0;
    int32_t m_height = 0;
};