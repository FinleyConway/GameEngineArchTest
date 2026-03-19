#include "utils/to_rl.hpp"

namespace test
{
    ::Vector2 ToRl::from_vector2f(Vector2f v) {
        return {
            .x = v.x,
            .y = v.y
        };
    }

    ::Rectangle ToRl::from_float_rect(FloatRect r) {
        return {
            .x = r.x,
            .y = r.y,
            .width = r.w,
            .height = r.h
        };
    }
}