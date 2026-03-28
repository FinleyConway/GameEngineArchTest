#pragma once

#include <cassert>
#include <cstdint>
#include <type_traits>

#include "rail_types.hpp"

class Rail
{
public:
    Rail() = default;

    explicit Rail(Type type) : m_type(type) { }

    Type get_type() const {
        return m_type;
    }

    void set_type(Type type) {
        m_type = type;
    }

    void set_flow(Dir a, Dir b) {
        uint8_t bits = to_bits(a) | to_bits(b);

        assert((to_bits(m_type) & bits) == bits && "No flow state for this rail type");

        m_active_mask = bits;
    }

    bool is_direction_active(Dir d) const {
        uint8_t bit = to_bits(d);

        if (!has_dir(bit)) return false;
        if (!is_junction_type(m_type)) return true;

        return (m_active_mask & bit) != 0;
    }

    Dir try_get_exit(Dir from) const {
        if (!is_direction_active(from)) return Dir::None;

        if (!is_junction_type(m_type)) {
            uint8_t other = to_bits(m_type) ^ to_bits(from);

            return from_bits(other);
        }

        uint8_t other = m_active_mask ^ to_bits(from);

        return from_bits(other);
    }

private:
    template<typename Enum>
    std::underlying_type_t<Enum> to_bits(Enum e) const {
        return std::underlying_type_t<Enum>(e);
    }

    Dir from_bits(uint8_t bits) const {
        switch (bits) {
            case 1:   return Dir::N;
            case 2:   return Dir::NE;
            case 4:   return Dir::E;
            case 8:   return Dir::SE;
            case 16:  return Dir::S;
            case 32:  return Dir::SW;
            case 64:  return Dir::W;
            case 128: return Dir::NW;
            default:  return Dir::None;
        }
    }

    bool has_dir(uint8_t dir) const {
        return to_bits(m_type) & dir;
    }

    bool is_junction_type(Type type) const {
        switch (type) {
            case Type::TJunctionDown:   return true;
            case Type::TJunctionUp:     return true;
            case Type::TJunctionLeft:   return true;
            case Type::TJunctionRight:  return true;
            case Type::CrossJunction:   return true;
            default:                    return false;
        }
    }

private:
    Type m_type = Type::None;
    uint8_t m_active_mask = 0;
};