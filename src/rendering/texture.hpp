#pragma once

#include <string>

#include <raylib.h>

namespace test
{
    class Texture
    {
    public:
        Texture();

        explicit Texture(const std::string& file_name);

        ~Texture();

        static Texture create_rectangle(int width, int height, Color color);

        bool is_valid() const;

        const Texture2D& get_handle() const;

    private:
        Texture2D m_handle;
    };
}