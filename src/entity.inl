#pragma once

#include "scene.h"

template<typename T>
T* Entity::add_component()
{
    if (!is_valid()) return nullptr;

    return m_scene->get_entity_storage(m_handle).template add_component<T>(*this);
}

template<typename T>
T* Entity::get_component()
{
    if (!is_valid()) return nullptr;

    return m_scene->get_entity_storage(m_handle).template get_component<T>();
}

template<typename T>
const T* Entity::get_component() const
{
    if (!is_valid()) return nullptr;

    return m_scene->get_entity_storage(m_handle).template get_component<T>();
}

template<typename T>
bool Entity::remove_component() const
{
    if (!is_valid()) return false;

    return m_scene->get_entity_storage(m_handle).template remove_component<T>();
}