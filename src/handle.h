#pragma once

#include <cstdint>
#include <limits>

struct Handle 
{
using Type = uint32_t;

public:
    Type id;
    Type generation;

    Handle() : id(invalid_type_value()), generation(invalid_type_value()) { }
    Handle(Type id, Type generation) : id(id), generation(generation) {}

    bool is_valid() const {
        const Type invalid = invalid_type_value();

        return id != invalid && generation != invalid;
    }

    static constexpr Handle invalid_handle_value() {
        const Type invalid = invalid_type_value();

        return Handle(invalid, invalid);
    }

    static constexpr Type invalid_type_value() {
        return std::numeric_limits<Type>::max();
    }
};