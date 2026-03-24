#pragma once

#include <raylib.h>

#include <string>

namespace test
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title, int flags = 0) {
            ::SetConfigFlags(flags);
            ::InitWindow(width, height, title.c_str());
        }

        ~Window() {
            ::CloseWindow();
        }

        bool is_window_open() const {
            return !::WindowShouldClose();
        }
    };
}