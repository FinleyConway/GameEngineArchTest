#pragma once

#include <vector>

#include "entity_storage.h"
#include "sparse_set.h"
#include "entity.h"
#include "handle.h"

struct ActiveComponents
{
    Handle handle;
    ComponentBase* component = nullptr;

    Handle::Type get_id() const {
        return handle.id;
    }
};

class Entity;

// an event based update approach would be nice and stuff that needs continous updates such as rendering and listen to on added components
// add labels to each component such as on_event, on_update
// on_event will listen to events from other components or polling events etc
// on_update will simply be on the main thread
// can bitwise these flags so that components can listen two both
// can have dedicated systems that listen for certain components such as SpriteRenderer which simply adds it to a QuadTree etc

class Scene 
{
public:
    Scene(Handle::Type max_entities);

    Entity create_entity();
    void destroy_entity(Entity entity);

    void update() {
        for (auto& entity : m_entities.data()) {
            entity.update_components();
        }
    }

private:
    Handle generate_handle();
    void return_handle(Handle handle);

    EntityStorage& get_entity_storage(Handle handle);

private:
    friend class Entity;

private:
    // stores all the entities within the scene
    // - will be used to call start() so components can set up xyz such as event listening
    // - easy way to serialise all data since its in one place
    SparseSet<Handle::Type, EntityStorage> m_entities;

    // stores all entities that need on demand updates
    // - will be iteration each frame on these 
    // - can use the entity id to find the active component if removal etc needs to occur
    SparseSet<Handle::Type, ActiveComponents> m_active_entities;

    std::vector<Handle> m_free_entities; // stores non active handles that can be reused
    Handle::Type m_max_entities; // max entities in one scene
};