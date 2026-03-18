#pragma once

#include <raylib.h>

namespace test {
    class Camera 
    {
    public:
        float get_zoom() const {
            return m_zoom;
        }

    private:
        float m_zoom = 1;
    };
}