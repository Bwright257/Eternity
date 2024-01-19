#pragma once
#include "World.h"
#include "EntityManager.h"

class Slate{
    public:
        Slate() : _entityManager(this){}
        ~Slate(){}

        World& world(){return _world;}
        const World& world() const{return _world;}
        EntityManager& entityManager(){return _entityManager;}
        const EntityManager& entityManager() const{return _entityManager;}
    private:
        World _world;
        EntityManager _entityManager;
};