#pragma once

#include <cstdint>

#include "entity.h"

using TypeID = uint32_t;

class TypeIDGenerator
{
public:
    template<typename T>
    static TypeID create_id() {
        static TypeID id = m_counter++;
        return id;
    }

private:
    inline static TypeID m_counter = 0;
};

class ComponentBase 
{
public:
    virtual ~ComponentBase() = default;

public:
    virtual TypeID get_id() const = 0;
    virtual void start() { };
    virtual void update() { };
};

template<typename TComponent>
class Component : ComponentBase
{
public:
    TypeID get_id() const override {
        return get_id_static();
    } 

    void start() override { };
    void update() override { };

    Entity entity() {
        return m_entity;
    }

private:
    friend class EntityStorage;

    static TypeID get_id_static() {
        return TypeIDGenerator::create_id<TComponent>();
    }

    void set_entity(Entity entity) {
        m_entity = entity;
    }

private:
    Entity m_entity;
};