#pragma once
#include "Area.h"
#include "EntityManager.h"

class Slate{
    public:
        Slate(std::shared_ptr<Area> area) : _area(std::move(area)), _entityManager(_area.get()){}
        ~Slate(){}

        Area* area(){return _area.get();}
        const Area* area() const{return _area.get();}
        EntityManager& entityManager(){return _entityManager;}
        const EntityManager& entityManager() const{return _entityManager;}
    private:
        std::shared_ptr<Area> _area;
        EntityManager _entityManager;
};