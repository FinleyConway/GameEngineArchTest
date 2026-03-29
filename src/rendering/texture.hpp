#pragma once

#include <string>

#include <raylib.h>

namespace mz
{
    class Texture
    {
    public:
        Texture();

        explicit Texture(const std::string& file_name);

        ~Texture();

        static Texture create_rectangle(int width, int height, Color color);

        bool is_valid() const;

    private:
        friend class Renderer;

        const Texture2D& get_handle() const;

    private:
        Texture2D m_handle;
    };
}