#pragma once

struct Vector2;

namespace test
{
    class Renderable
    {
    public:
        virtual ~Renderable() = default;

    protected:
        friend class RenderSystem;

        virtual void draw(Vector2 position) const = 0;
    };
}