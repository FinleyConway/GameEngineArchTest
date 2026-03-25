#pragma once

#include <vector>
#include <cassert>
#include <unordered_map>

#include <entt/entt.hpp>

#include "math/rect.hpp"

namespace test 
{
    // Allow to split up the scene into fixed sized chunks to allow querying from a region.
    class SpatialIndex
    {
    struct FixedBounds;
    struct Cell;

    public:
        explicit SpatialIndex(float cell_size);

        // Inserts an entity into the spatial grid using its bounding box.
        void insert(entt::entity entity, const FloatRect& bounds);

        // Remove an entity from the spatial grid using its bounding box.
        void remove(entt::entity entity, bool remove_empty = false);

        // Query a collection of entities using a given bounding box.
        template<typename Fn>
        void query(const FloatRect& bounds, Fn&& fn) {
            std::vector<entt::entity> visited;
            FixedBounds fb = to_fixed_bounds(bounds);
            
            for (int32_t cx = fb.min_x; cx <= fb.max_x; cx++) {
                for (int32_t cy = fb.min_y; cy <= fb.max_y; cy++) {
                    if (auto it = m_cells.find(Cell(cx, cy)); it != m_cells.end()) {
                        get_unique(it->second, visited, std::forward<Fn>(fn));
                    }
                }
            }
        }

    private:
        // Get unique entity back comparing a visted
        template<typename Fn>
        void get_unique(const std::vector<entt::entity>& vec, std::vector<entt::entity>& visited, Fn&& fn) const {
            for (auto entity : vec) {
                if (std::find(visited.begin(), visited.end(), entity) == visited.end()) {
                    visited.emplace_back(entity);
                    std::forward<Fn>(fn)(entity);
                }
            }
        }

        // Swap and pop entity with the last element to prevent erase() shifting
        bool swap_pop(entt::entity entity, std::vector<entt::entity>& vec) const;

        // Convert AABB to fixed bounds
        FixedBounds to_fixed_bounds(const FloatRect& bounds) const;

        // Convert position_axis to a grid axis.
        int32_t to_cell(float position_axis) const;
    
    private:
        struct FixedBounds
        {
            int32_t min_x = 0;
            int32_t min_y = 0;
            int32_t max_x = 0;
            int32_t max_y = 0;
        };

        struct Cell 
        {
            int32_t x;
            int32_t y;

            Cell(int32_t x, int32_t y) : x(x), y(y) { }

            bool operator==(const Cell& other) const {
                return x == other.x && y == other.y;
            }

            struct Hash
            {
                size_t operator()(const Cell& cell) const {
                    // https://stackoverflow.com/a/55083395
                    size_t hash = std::hash<int32_t>()(cell.x);

                    hash <<= sizeof(size_t) * 4;
                    hash ^= std::hash<int32_t>()(cell.y);

                    return std::hash<size_t>()(hash);
                }
            };
        };

    private:
        std::unordered_map<Cell, std::vector<entt::entity>, Cell::Hash> m_cells; // i could honestly replace this with a flat vector, even if worlds infinite
        std::unordered_map<entt::entity, std::vector<Cell>> m_entity_cells;
        float m_cell_size = 0;
    };
}