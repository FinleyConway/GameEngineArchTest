#pragma once

class Entity;

template<typename T>
concept Updatable = requires(T t, Entity e, float dt)
{
    t.update(e, dt);
};