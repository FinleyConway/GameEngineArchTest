#pragma once

#include "core/input/key.hpp"
#include "core/input/mouse.hpp"
#include "math/vector2.hpp"

namespace test 
{
    class Input
    {
    public:
        static bool is_key_down(Key key);

        static bool is_key_held(Key key);

        static bool is_key_up(Key key);

        static Vector2f get_mouse_position();

        static bool is_mouse_down(MouseButton button);

        static bool is_mouse_held(MouseButton button);

        static bool is_mouse_up(MouseButton button);

        static float get_mouse_axis();

    private:
        static int key_to_raylib(Key key);

        static int mouse_to_raylib(MouseButton key);
    };
}