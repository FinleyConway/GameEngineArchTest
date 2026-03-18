#pragma once

#include <string.h>

#include <raylib.h>

namespace test
{
    class Texture
    {
    public:
        explicit Texture() : m_handle({}) {
        }

        explicit Texture(const std::string& file_name) {
            m_handle = ::LoadTexture(file_name.c_str());
        }

        ~Texture() {
            if (m_handle.id != 0) {
                ::UnloadTexture(m_handle);
                m_handle = {};
            }
        }

        static Texture create_rectangle(int width, int height, Color color)
        {
            Image img = ::GenImageColor(width, height, color);
            Texture tex;

            tex.m_handle = ::LoadTextureFromImage(img);
            ::UnloadImage(img);

            return tex;
        }

        bool is_valid() const {
            return ::IsTextureValid(m_handle);
        }

        const Texture2D& get_handle() const { return m_handle; }

    private:
        Texture2D m_handle;
    };
}