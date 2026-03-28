#pragma once

#include <expected>
#include <cstdint>
#include <functional>
#include <vector>

#include "math/vector2.hpp"

enum class GridError {
    None,
    IsEmpty,
    OutOfBounds
};

template <typename T>
using CellRef = std::expected<std::reference_wrapper<T>, GridError>;

template <typename T>
using CellCRef = std::expected<std::reference_wrapper<const T>, GridError>;

template<typename T>
class Grid 
{
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

    CellRef<T> get(int32_t x, int32_t y) {
        if (m_data.empty()) return std::unexpected(GridError::IsEmpty);
        if (!is_within(x, y)) return std::unexpected(GridError::OutOfBounds);

        return std::ref(m_data[get_index(x, y)]);
    }

    CellRef<T> get(test::Vector2i position) {
        return get(position.x, position.y);
    }

    CellCRef<T> get(int32_t x, int32_t y) const {
        if (m_data.empty()) return std::unexpected(GridError::IsEmpty);
        if (!is_within(x, y)) return std::unexpected(GridError::OutOfBounds);

        return std::cref(m_data[get_index(x, y)]);
    }

    CellCRef<T> get(test::Vector2i position) const {
        return get(position.x, position.y);
    }

    GridError set(int32_t x, int32_t y, const T& value) {
        if (m_data.empty()) return GridError::IsEmpty;
        if (!is_within(x, y)) return GridError::OutOfBounds;

        m_data[get_index(x, y)] = value;

        return GridError::None;
    }

    GridError set(test::Vector2i position, const T& value) {
        return set(position.x, position.y, value);
    }

private:
    int32_t get_index(int32_t x, int32_t y) const {
        return x + m_width * y;
    }

private:
    std::vector<T> m_data;
    int32_t m_width = 0;
    int32_t m_height = 0;
};