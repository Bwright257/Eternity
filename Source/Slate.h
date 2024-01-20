#pragma once
#include "Area.h"
#include "EntityManager.h"

class Slate{
    public:
        Slate(int slateID, std::shared_ptr<Area> area) : _slateID(slateID), _area(std::move(area)), _entityManager(_area.get()){}
        ~Slate(){}

        const int& slateID(){return _slateID;}
        Area* area(){return _area.get();}
        const Area* area() const{return _area.get();}
        EntityManager& entityManager(){return _entityManager;}
        const EntityManager& entityManager() const{return _entityManager;}
    private:
        const int _slateID;
        std::shared_ptr<Area> _area;
        EntityManager _entityManager;
};