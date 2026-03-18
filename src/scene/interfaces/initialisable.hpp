#pragma once

namespace test 
{
    class Entity;

    class Initialisable 
    {
    public:
        virtual void start(Entity e) = 0;

    protected:
        friend class Scene;

        virtual ~Initialisable() = default;
    };
}