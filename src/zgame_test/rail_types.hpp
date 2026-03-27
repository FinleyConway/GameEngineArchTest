#pragma once

#include <array>
#include <cstdint>
#include <type_traits>

enum class Dir : uint8_t
{
    None = 0,	// 00000000
    N    = 1,   // 00000001
    NE   = 2,   // 00000010
    E    = 4,   // 00000100
    SE   = 8,   // 00001000
    S    = 16,  // 00010000
    SW   = 32,  // 00100000
    W    = 64,  // 01000000
    NW   = 128  // 10000000
};

enum class Type : uint8_t
{
    // Empty
    None            = static_cast<uint8_t>(Dir::None),                               

    // │
    NorthSouth      = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::S),  

    // ─
    WestEast        = static_cast<uint8_t>(Dir::W) | static_cast<uint8_t>(Dir::E),    

    // └
    NorthEast       = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::E),    

    // ┘
    NorthWest       = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::W),    

    // ┌
    SouthEast       = static_cast<uint8_t>(Dir::S) | static_cast<uint8_t>(Dir::E),    

    // ┐
    SouthWest       = static_cast<uint8_t>(Dir::S) | static_cast<uint8_t>(Dir::W),    

    // ┬
    TJunctionDown   = WestEast   | static_cast<uint8_t>(Dir::S),

    // ┴
    TJunctionUp     = WestEast   | static_cast<uint8_t>(Dir::N),

    // ┤
    TJunctionLeft   = NorthSouth | static_cast<uint8_t>(Dir::W),

    // ├
    TJunctionRight  = NorthSouth | static_cast<uint8_t>(Dir::E),

    // ┼
    CrossJunction   = NorthSouth | WestEast,
};

std::array<Dir, 12> get_all_dirs() {
    return { Dir::N, Dir::NE, Dir::E, Dir::SE, Dir::S, Dir::SW, Dir::W, Dir::NW };
}

template<typename Enum>
static std::underlying_type_t<Enum> to_bits(Enum e) {
    return std::underlying_type_t<Enum>(e);
}

Dir from_bits(uint8_t bits) {
    switch (bits) {
        case 1:   return Dir::N;
        case 2:   return Dir::NE;
        case 4:   return Dir::E;
        case 8:   return Dir::SE;
        case 16:  return Dir::S;
        case 32:  return Dir::SW;
        case 64:  return Dir::W;
        case 128: return Dir::NW;
        default:  return Dir::None;
    }
}