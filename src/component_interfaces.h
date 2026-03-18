#pragma once

#include <raylib.h>

namespace test {
    class Entity;

    class IInitialisable 
    {
    public:
        virtual void start(Entity e) = 0;

    protected:
        friend class Scene;

        virtual ~IInitialisable() = default;
    };

    class IUpdatable 
    {
    public:
        virtual ~IUpdatable() = default;

    protected:
        friend class Scene;

        virtual void update(Entity e, float dt) = 0;
    };

    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;

    protected:
        friend class Render;

        virtual void draw(Vector2 position) const = 0;
    };
}