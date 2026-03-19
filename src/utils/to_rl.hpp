#pragma once

#include <raylib.h>

#include "math/vector2.hpp"
#include "math/rect.hpp"

namespace test 
{
    class ToRl
    {
    public:
        static ::Vector2 from_vector2f(Vector2f v) {
            return {
                .x = v.x,
                .y = v.y
            };
        }

        static ::Rectangle from_float_rect(FloatRect r) {
            return {
                .x = r.x,
                .y = r.y,
                .width = r.w,
                .height = r.h
            };
        }
    };
}