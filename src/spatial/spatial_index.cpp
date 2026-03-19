#include "spatial/spatial_index.hpp"

namespace test
{
    SpatialIndex::SpatialIndex(float cell_size) : m_cell_size(cell_size) {
        assert((void("spatial index cell size must not be 0"), cell_size != 0.0f));
    }

    void SpatialIndex::insert(entt::entity entity, const FloatRect& bounds) {
        FixedBounds fb = to_fixed_bounds(bounds);

        for (int32_t cx = fb.min_x; cx <= fb.max_x; cx++) {
            for (int32_t cy = fb.min_y; cy <= fb.max_y; cy++) {
                Cell cell(cx, cy);

                m_cells[cell].emplace_back(entity);
                m_entity_cells[entity].emplace_back(cell);
            }
        }
    }

    void SpatialIndex::remove(entt::entity entity, bool remove_empty) {
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

    bool SpatialIndex::swap_pop(entt::entity entity, std::vector<entt::entity>& vec) const {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i] == entity) {
                vec[i] = vec.back(); 
                vec.pop_back();

                return true;
            }
        }

        return false;
    }

    SpatialIndex::FixedBounds SpatialIndex::to_fixed_bounds(const FloatRect& bounds) const {
        return {
            .min_x = to_cell(bounds.x),
            .min_y = to_cell(bounds.y),
            .max_x = to_cell(bounds.x + bounds.w),
            .max_y = to_cell(bounds.y + bounds.h),
        };
    }

    int32_t SpatialIndex::to_cell(float position_axis) const {
        return static_cast<int32_t>(std::floor(position_axis / m_cell_size));
    }
}