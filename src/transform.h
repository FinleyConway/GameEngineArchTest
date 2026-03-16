#pragma once

#include <string>

class Transform
{
public:
    float x = 0;
    float y = 0;

    std::string to_str() const {
        return std::format("[x:{}, y:{}]", x, y);
    }
};