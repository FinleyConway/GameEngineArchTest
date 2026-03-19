#pragma once

#include <raylib.h>

#include "core/input/key.hpp"
#include "core/input/mouse.hpp"
#include "math/vector2.hpp"

namespace test 
{
    class Input
    {
    public:
        static bool is_key_down(Key key) {
            return ::IsKeyPressed(key_to_raylib(key));
        }

        static bool is_key_held(Key key) {
            return ::IsKeyDown(key_to_raylib(key));
        }

        static bool is_key_up(Key key) {
            return ::IsKeyReleased(key_to_raylib(key));
        }

        static Vector2f get_mouse_position() {
            ::Vector2 mouse_position = ::GetMousePosition();

            return Vector2f(mouse_position.x, mouse_position.y);
        }

        static bool is_mouse_down(MouseButton button)
        {
            return ::IsMouseButtonPressed(mouse_to_raylib(button));
        }

        static bool is_mouse_held(MouseButton button)
        {
            return ::IsMouseButtonDown(mouse_to_raylib(button));
        }

        static bool is_mouse_up(MouseButton button)
        {
            return ::IsMouseButtonReleased(mouse_to_raylib(button));
        }

        static float get_mouse_axis()
        {
            return ::GetMouseWheelMove();
        }

    private:
        static int key_to_raylib(Key key)
        {
            return static_cast<int>(key);
        }

        static int mouse_to_raylib(MouseButton key)
        {
            return static_cast<int>(key);
        }
    };
}