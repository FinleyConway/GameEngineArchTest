#include "scene.h"

#include "entity.h"

Scene::Scene(Handle::Type max_entities) : m_entities(max_entities), m_active_entities(max_entities), m_max_entities(m_max_entities) {}

Entity Scene::create_entity() {
    Handle handle = generate_handle();

    m_entities.insert(EntityStorage(handle));

    return Entity(handle, this);
}

void Scene::destroy_entity(Entity entity) {
    m_entities.remove(entity.m_handle.id);

    return_handle(entity.m_handle);
}

Handle Scene::generate_handle() {
    if (!m_free_entities.empty()) {
        Handle id = m_free_entities.back();
        m_free_entities.pop_back();

        id.generation++;

        return id;
    }

    static Handle::Type id = 0;

    if (id > m_max_entities) {
        return Handle::invalid_handle_value();
    }

    return Handle(id++, 0);
}

void Scene::return_handle(Handle handle) {
    m_free_entities.emplace_back(handle);
}

EntityStorage& Scene::get_entity_storage(Handle handle) {
    return m_entities.get(handle.id);
}