#pragma once

#include <cassert>

#include "rail_types.hpp"

class Rail
{
public:
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

    Dir get_exit(Dir from) const {
        uint8_t f = to_bits(from);

        // must be part of the rail
        if (!(to_bits(m_type) & f))
            return Dir::None;

        // not a junction so just return the other connected direction
        if (!is_junction_type(m_type))
        {
            uint8_t other = to_bits(m_type) ^ f;
            return from_bits(other);
        }

        // is a junction so must follow active flow
        if (!(m_active_mask & f))
            return Dir::None;

        uint8_t other = m_active_mask ^ f;

        return from_bits(other);
    }

    bool can_travel_to(Dir d) const {
        uint8_t bit = to_bits(d);

        if (!(to_bits(m_type) & bit))
            return false;

        if (!is_junction_type(m_type))
            return true;

        return (m_active_mask & bit) != 0;
    }

private:
    bool is_junction_type(Type type) const
    {
        switch (type)
        {
            case Type::TJunctionDown:   return true;
            case Type::TJunctionUp:     return true;
            case Type::TJunctionLeft:   return true;
            case Type::TJunctionRight:  return true;
            case Type::CrossJunction:   return true;
            default:                    return false;
        }
    }

private:
    Type m_type;
    uint8_t m_active_mask = 0;
};