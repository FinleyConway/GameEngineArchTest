#pragma once

#include "handle.h"

class Scene; 

class Entity
{
public:
    Entity() = default;

    Handle::Type get_id() { return m_handle.id; }

    template<typename T> T* add_component();
    template<typename T> T* get_component();
    template<typename T> const T* get_component() const;
    template<typename T> bool remove_component() const;

    bool is_valid() const { return m_handle.is_valid() && m_scene != nullptr; }

private:
    friend class Scene;
    friend class EntityStorage;

    Entity(Handle handle, Scene* scene) : m_handle(handle), m_scene(scene) {}

private:
    Handle m_handle;
    Scene* m_scene = nullptr;
};

#include "entity.inl"