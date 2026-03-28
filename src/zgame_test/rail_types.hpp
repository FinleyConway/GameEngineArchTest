#pragma once

#include <cstdint>

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
    None           = static_cast<uint8_t>(Dir::None),                             // Empty                               
    NorthSouth     = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::S), // │
    WestEast       = static_cast<uint8_t>(Dir::W) | static_cast<uint8_t>(Dir::E), // ─   
    NorthEast      = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::E), // └   
    NorthWest      = static_cast<uint8_t>(Dir::N) | static_cast<uint8_t>(Dir::W), // ┘   
    SouthEast      = static_cast<uint8_t>(Dir::S) | static_cast<uint8_t>(Dir::E), // ┌   
    SouthWest      = static_cast<uint8_t>(Dir::S) | static_cast<uint8_t>(Dir::W), // ┐    
    TJunctionDown  = WestEast   | static_cast<uint8_t>(Dir::S),                   // ┬
    TJunctionUp    = WestEast   | static_cast<uint8_t>(Dir::N),                   // ┴
    TJunctionLeft  = NorthSouth | static_cast<uint8_t>(Dir::W),                   // ┤
    TJunctionRight = NorthSouth | static_cast<uint8_t>(Dir::E),                   // ├
    CrossJunction  = NorthSouth | WestEast,                                       // ┼
};