#pragma once

namespace test
{
    class Entity;

    class Updatable 
    {
    public:
        virtual ~Updatable() = default;

    protected:
        friend class Scene;

        virtual void update(Entity e, float dt) = 0;
    };
}