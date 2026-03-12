#pragma once

#include "sparse_map.h"
#include "component.h"
#include "handle.h"
#include "entity.h"

class EntityStorage 
{
public:
    EntityStorage(Handle handle) : m_handle(handle) { }

    ~EntityStorage() {
        for (const auto* component : m_components.data()) {
            delete component;
        }
    }

    Handle::Type get_id() const {
        return m_handle.id;
    }

    template<typename T>
    T* add_component(Entity entity) {
        static_assert(std::is_base_of_v<ComponentBase, T>, "T must derive from ComponentBase");

        if (m_components.contains(T::get_id_static())) {
            return get_component<T>();
        }

        T* component = new T;
        component->set_entity(entity);  
        m_components.insert(component);

        return get_component<T>();
    }

    template<typename T>
    T* get_component() {
        static_assert(std::is_base_of_v<ComponentBase, T>, "T must derive from ComponentBase");

        auto id = T::get_id_static();

        if (m_components.contains(id)) {
            return static_cast<T*>(m_components.get(id));
        }

        return nullptr;
    }

    template<typename T>
    const T* get_component() const {
        static_assert(std::is_base_of_v<ComponentBase, T>, "T must derive from ComponentBase");

        return get_component<T>();
    }

    template<typename T>
    bool remove_component() {
        static_assert(std::is_base_of_v<ComponentBase, T>, "T must derive from ComponentBase");

        if (m_components.contains(T::get_id_static())) {
            delete m_components.get(T::get_id_static());

            m_components.remove(T::get_id_static());

            return true;
        }

        return false;
    }

    void update_components() {
        for (ComponentBase* component : m_components.data()) {
            if (component != nullptr) {
                component->update();
            }
        }
    }

private:
    Handle m_handle;
    SparseMap<TypeID, ComponentBase*> m_components; 
};