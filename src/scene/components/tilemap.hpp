#pragma once

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cstdint>

#include "math/vector2.hpp"

namespace mz 
{
    class Tilemap
    {
    using TileID = uint16_t;    
    struct Chunk;

    public:
        explicit Tilemap(uint32_t chunkSize) : 
            m_chunk_size(chunkSize), m_chunk_area(chunkSize * chunkSize) {
        }

        TileID get_tile(Vector2i position) const {
            if (auto* chunk = try_get_chunk(position)) {
                if (chunk->tiles.size() == m_chunk_area) {
                    return chunk->tiles[get_index(position)];
                }
            }

            return c_empty_tile;
        }

        bool has_tile(Vector2i position) const {
            return get_tile(position) != c_empty_tile;
        }

        void place_tile(Vector2i position, TileID tile) {
            auto& chunk = get_chunk(position);

            chunk.tiles[get_index(position)] = tile;
            chunk.dirty = true;
        }

        void remove_tile(Vector2i position) {
            Vector2i chunk_pos = grid_to_chunk(position);

            if (auto it = m_tilemap.find(chunk_pos); it != m_tilemap.end()) {
                auto& chunk = it->second;

                chunk.tiles[get_index(position)] = c_empty_tile;
                chunk.dirty = true;

                try_remove_chunk(chunk_pos);
            }
        }

    private:
        Chunk& get_chunk(Vector2i position)
        {
            Vector2i chunk_pos = grid_to_chunk(position);
            auto& chunk = m_tilemap[chunk_pos];

            if (chunk.tiles.size() != m_chunk_area)
            {
                chunk.tiles.resize(m_chunk_area, c_empty_tile);
                chunk.dirty = true;
            }

            return chunk;
        }

        Chunk* try_get_chunk(Vector2i position) {
            auto it = m_tilemap.find(grid_to_chunk(position));

            return (it != m_tilemap.end()) ? &it->second : nullptr;
        }

        const Chunk* try_get_chunk(Vector2i position) const {
            auto it = m_tilemap.find(grid_to_chunk(position));

            return (it != m_tilemap.end()) ? &it->second : nullptr;
        }

        void try_remove_chunk(Vector2i chunk_pos) {
            auto it = m_tilemap.find(chunk_pos);
            if (it == m_tilemap.end()) return;

            const auto& tiles = it->second.tiles;

            if (std::all_of(tiles.begin(), tiles.end(), [](TileID t) { return t == c_empty_tile; })) {
                m_tilemap.erase(it);
            }
        }

        Vector2i grid_to_chunk(Vector2i position) const {
            return Vector2i(
                position.x >= 0 ? position.x / m_chunk_size : (position.x - m_chunk_size + 1) / m_chunk_size, 
                position.y >= 0 ? position.y / m_chunk_size : (position.y - m_chunk_size + 1) / m_chunk_size
            );
        }

        Vector2i grid_to_local(Vector2i position) const {
            int32_t local_x = position.x % m_chunk_size;
            int32_t local_y = position.y % m_chunk_size;

            if (local_x < 0) local_x += m_chunk_size;
            if (local_y < 0) local_y += m_chunk_size;

            return Vector2i(local_x, local_y);
        }

        int32_t get_index(Vector2i position) const {
            Vector2i local = grid_to_local(position);

            return local.x + local.y * m_chunk_size;
        }

    private:
        struct Chunk
        {
            std::vector<TileID> tiles;
            bool dirty = true;
        };

    private:
        std::unordered_map<Vector2i, Chunk, Vector2i::Hash> m_tilemap;
        uint32_t m_chunk_size;
        uint32_t m_chunk_area;

        static constexpr TileID c_empty_tile = 0;
    };
}