#pragma once
#include <map>
#include <memory>
#include "Entity.h"

class Slate;
class EntityManager{
    public:
        EntityManager(Slate* slate) : _slate(slate){}
        ~EntityManager(){}

        void moveEntity(int entityID, Direction direction);

        Entity* entity(int entityID);
        Entity* entityAt(Location location);
        bool entityExists(int entityID);
        bool entityExistsAt(Location location);
        Entity* createEntity(EntityType type, Location location);
        void destroyEntity(int entityID);

        Slate* slate(){return _slate;}
        const Slate* slate() const{return _slate;}
        std::map<int, std::shared_ptr<Entity>>& entities(){return _entities;}
        const std::map<int, std::shared_ptr<Entity>>& entities() const{return _entities;}
    private:
        Slate* _slate;
        std::map<int, std::shared_ptr<Entity>> _entities;
};