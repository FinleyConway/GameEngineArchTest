#pragma once

#include "math/vector2.hpp"
#include "scene/entity.hpp"
#include "scene/interfaces/initialisable.hpp"
#include "scene/interfaces/singleton.hpp"

#include "zgame_test/grid.hpp"
#include "zgame_test/rail.hpp"

class RailMap : public test::Initialisable, public test::Singleton<RailMap>
{
public:
    void start(test::Entity e) {
        m_rails = Grid<Rail>(m_width, m_height);

        set_rail({ 0, 0 }, Type::NorthEast);
        set_rail({ 1, 0 }, Type::WestEast);
        set_rail({ 2, 0 }, Type::NorthWest);

        set_rail({ 0, 1 }, Type::NorthSouth);
        set_rail({ 2, 1 }, Type::NorthSouth);

        set_rail({ 0, 2 }, Type::SouthEast);
        set_rail({ 1, 2 }, Type::WestEast);
        set_rail({ 2, 2 }, Type::SouthWest);
    }

    int32_t get_cell_size() const {
        return m_cell_size;
    }

    GridError set_rail(test::Vector2i position, Type rail) {
        return m_rails.set(position, Rail(rail));
    }

    std::expected<const Rail*, GridError> get_rail(test::Vector2i position) const {
        return m_rails.get(position);
    }

private:
    Grid<Rail> m_rails;
    int32_t m_width = 3;
    int32_t m_height = 3;
    int32_t m_cell_size = 32;
};