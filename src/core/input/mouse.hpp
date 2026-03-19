#pragma once

#include <raylib.h>

namespace test
{
    enum class MouseButton : int
    {
        Left    = MOUSE_BUTTON_LEFT,
        Right   = MOUSE_BUTTON_RIGHT,
        Middle  = MOUSE_BUTTON_MIDDLE,

        Side    = MOUSE_BUTTON_SIDE,
        Extra   = MOUSE_BUTTON_EXTRA,
        Forward = MOUSE_BUTTON_FORWARD,
        Back    = MOUSE_BUTTON_BACK
    };
}