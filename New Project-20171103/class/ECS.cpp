#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
    static ComponentID typeID = GetComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
    Entity* m_pEntity;
    
    virtual void Initialize(){}
    virtual void Update(){}
    virtual void Draw(){}
    
    virtual ~Component(){}
};


class Entity
{
private:
    bool m_bActive;
    std::vector<std::unique_ptr<Component>> m_Components;
    
    ComponentArray m_ComponentArray;
    ComponentBitSet m_ComponentBitSet;
public:
    void Update()
    {
        for(auto& c : m_Components) c->Update();
        for(auto& c : m_Components) c->Draw();
    }
    
    void Draw(){}
    bool IsActive() const { return m_bActive; }
    void Destroy() { m_bActive = false; }
    
    template <typename T> bool HasComponent() const
    {
        return m_ComponentBitSet(GetComponentTypeID<T>);
    }

    template <typename T, typename... TArgs>
    T& AddComponent( TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->m_pEntity = this;
        std::unique_ptr<Component> uPtr(c);
        m_Components.emplace_back(std::move(uPtr));
        
        
        m_ComponentArray[GetComponentTypeID<T>()] = c;
        m_ComponentBitSet[GetComponentTypeID<T>()] = true;
        
        c->Initialize();
        return *c;
    }
    
    template<typename T> T& GetComponent() const
    {
        auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> m_Entities;
    
public:
    void Update()
    {
        for( auto& e : m_Entities) e->Update();
    }
    
    void Draw()
    {
        for( auto& e : m_Entities) e->Draw();
    }
    
    void Refresh()
    {
        m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities), 
        [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity->IsActive();
        }), std::end(m_Entities));
    }
    
    Entity& AddEntity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr( e );
        m_Entities.emplace_back(std::move(uPtr));
        return *e;
    }
};

