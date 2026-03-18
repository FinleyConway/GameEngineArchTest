#pragma once

#include <raylib.h>

namespace test {
    class Camera 
    {
    public:
        float get_zoom() const {
            return m_zoom;
        }

        void set_zoom(float zoom) {
            if (zoom <= 0.0f) return;

            m_zoom = zoom;
        }

    private:
        float m_zoom = 1;
    };
}