#include "rendering/texture.hpp"

namespace mz
{
    Texture::Texture() : m_handle({}) {
    }

    Texture::Texture(const std::string& file_name) {
        m_handle = ::LoadTexture(file_name.c_str());
    }

    Texture::~Texture() {
        if (m_handle.id != 0) {
            ::UnloadTexture(m_handle);
            m_handle = {};
        }
    }

    Texture Texture::create_rectangle(int width, int height, Color color)
    {
        Image img = ::GenImageColor(width, height, color);
        Texture tex;

        tex.m_handle = ::LoadTextureFromImage(img);
        ::UnloadImage(img);

        return tex;
    }

    bool Texture::is_valid() const {
        return ::IsTextureValid(m_handle);
    }

    const Texture2D& Texture::get_handle() const { return m_handle; }
}