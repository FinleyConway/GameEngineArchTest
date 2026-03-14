#pragma once

class Entity;

class IUpdatable
{
protected:
    friend class Scene; // feels very wrong doing this but it keeps the component api clean

    virtual void update(Entity entity, float dt) = 0;
};

class IInitialisable
{
protected:
    friend class Scene; // feels very wrong doing this but it keeps the component api clean

    virtual void start(Entity entity) = 0;
};

template<typename T>
concept Updatable = std::derived_from<T, IUpdatable>;

template<typename T>
concept Initialisable = std::derived_from<T, IInitialisable>;