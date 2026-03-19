#pragma once

#include "math/vector2.hpp"

namespace test
{
    class Renderable
    {
    public:
        virtual ~Renderable() = default;

    protected:
        friend class RenderSystem;

        virtual void draw(Vector2f position) const = 0;
    };
}