#include "core/input/input.hpp"

#include <raylib.h>

namespace test
{
    bool Input::is_key_down(Key key) {
        return ::IsKeyPressed(key_to_raylib(key));
    }

    bool Input::is_key_held(Key key) {
        return ::IsKeyDown(key_to_raylib(key));
    }

    bool Input::is_key_up(Key key) {
        return ::IsKeyReleased(key_to_raylib(key));
    }

    Vector2f Input::get_mouse_position() {
        ::Vector2 mouse_position = ::GetMousePosition();

        return Vector2f(mouse_position.x, mouse_position.y);
    }

    bool Input::is_mouse_down(MouseButton button) {
        return ::IsMouseButtonPressed(mouse_to_raylib(button));
    }

    bool Input::is_mouse_held(MouseButton button) {
        return ::IsMouseButtonDown(mouse_to_raylib(button));
    }

    bool Input::is_mouse_up(MouseButton button) {
        return ::IsMouseButtonReleased(mouse_to_raylib(button));
    }

    float Input::get_mouse_axis() {
        return ::GetMouseWheelMove();
    }

    int Input::key_to_raylib(Key key) {
        return static_cast<int>(key);
    }

    int Input::mouse_to_raylib(MouseButton key) {
        return static_cast<int>(key);
    }
}