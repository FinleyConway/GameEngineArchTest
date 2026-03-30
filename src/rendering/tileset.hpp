#pragma once

#include <vector>
#include <cstdint>

#include "math/rect.hpp"
#include "math/vector2.hpp"
#include "rendering/sprite.hpp"
#include "rendering/texture.hpp"

namespace mz 
{
    class Tileset
    {
    public:
        explicit Tileset(const std::string& file_path, Vector2<uint16_t> size, uint16_t tile_size) : 
            m_texture(file_path), m_size(size)
        {
            create(tile_size);
        }

        const Texture& get_texture() const {
            return m_texture;
        }

        const std::vector<Sprite>& get_all_tiles() const  {
            return m_tiles;
        }

        const Sprite* get_tile(Vector2<uint16_t> position) const {
            if (!has_tile(position)) return nullptr;

            return &m_tiles[position.y + m_size.y * position.x];
        }

        bool has_tile(Vector2<uint16_t> position) const {
            return position.x < m_size.x && position.y < m_size.y;
        }

    private:
        void create(uint16_t tile_size) {
            m_tiles.reserve(m_size.x * m_size.y);

            for (uint16_t x = 0; x < m_size.x; x++) {
                for (uint16_t y = 0; y < m_size.y; y++) {
                    m_tiles.emplace_back(m_texture, FloatRect(
                        static_cast<float>(x * tile_size),
                        static_cast<float>(y * tile_size),
                        static_cast<float>(tile_size),
                        static_cast<float>(tile_size)
                    ));
                }
            }
        }

    private:
        Texture m_texture;
        std::vector<Sprite> m_tiles;
        Vector2<uint16_t> m_size;
    };  
}