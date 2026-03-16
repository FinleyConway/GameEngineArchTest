#pragma once

#include <vector>
#include <cassert>
#include <unordered_map>

#include <entt/entt.hpp>

struct FixedBounds
{
    int32_t min_x = 0;
    int32_t min_y = 0;
    int32_t max_x = 0;
    int32_t max_y = 0;
};

struct AABB 
{
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;
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

// Allow to split up the scene into fixed sized chunks to allow querying from a region.
class SpatialIndex
{
public:
    explicit SpatialIndex(float cell_size) : m_cell_size(cell_size) {
        assert((void("spatial index cell size must not be 0"), cell_size != 0.0f));
    }

    // Inserts an entity into the spatial grid using its bounding box.
    void insert(entt::entity entity, const AABB& bounds) {
        FixedBounds fb = to_fixed_bounds(bounds);

        for (int32_t cx = fb.min_x; cx <= fb.max_x; cx++) {
            for (int32_t cy = fb.min_y; cy <= fb.max_y; cy++) {
                Cell cell(cx, cy);

                m_cells[cell].emplace_back(entity);
                m_entity_cells[entity].emplace_back(cell);
            }
        }
    }

    // Remove an entity from the spatial grid using its bounding box.
    void remove(entt::entity entity, bool remove_empty = false) {
        auto entity_it = m_entity_cells.find(entity);
        if (entity_it == m_entity_cells.end()) return;

        for (const auto& cell : entity_it->second) {
            if (auto it = m_cells.find(cell); it != m_cells.end()) {
                auto& vec = it->second;

                if (swap_pop(entity, vec) && vec.empty() && remove_empty) {
                    m_cells.erase(it);
                }
            }
        }

        m_entity_cells.erase(entity);
    }

    // Query a collection of entities using a given bounding box.
    template<typename Fn>
    void query(const AABB& bounds, Fn&& fn) {
        std::vector<entt::entity> visited;
        FixedBounds fb = to_fixed_bounds(bounds);
        
        for (int32_t cx = fb.min_x; cx <= fb.max_x; cx++) {
            for (int32_t cy = fb.min_y; cy <= fb.max_y; cy++) {
                if (auto it = m_cells.find(Cell(cx, cy)); it != m_cells.end()) {
                    get_unique(it->second, visited, fn);
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
                fn(entity);
            }
        }
    }

    // Swap and pop entity with the last element to prevent erase() shifting
    bool swap_pop(entt::entity entity, std::vector<entt::entity>& vec) const {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i] == entity) {
                vec[i] = vec.back(); 
                vec.pop_back();

                return true;
            }
        }

        return false;
    }

    // Convert AABB to fixed bounds
    FixedBounds to_fixed_bounds(const AABB& bounds) const {
        return {
            .min_x = to_cell(bounds.x),
            .min_y = to_cell(bounds.y),
            .max_x = to_cell(bounds.x + bounds.w),
            .max_y = to_cell(bounds.y + bounds.h),
        };
    }

    // Convert position_axis to a grid axis.
    int32_t to_cell(float position_axis) const {
        return static_cast<int32_t>(std::floor(position_axis / m_cell_size));
    }

private:
    std::unordered_map<Cell, std::vector<entt::entity>, Cell::Hash> m_cells; // i could honestly replace this with a flat vector, even if worlds infinite
    std::unordered_map<entt::entity, std::vector<Cell>> m_entity_cells;
    float m_cell_size = 0;
};