#pragma once
#include <map>
#include <memory>
#include "Entity.h"

class Area;
class EntityManager{
    public:
        EntityManager(Area* area) : _area(area){}
        ~EntityManager(){}

        void tick();

        void moveEntity(int entityID, Direction direction);
        bool canMoveTo(Location location);
        int distanceTo(Location start, Location end);
        Direction directionTo(Location start, Location end);
        std::set<Location> adjacentLocations(Location location);
        std::vector<Direction> pathTo(Location start, Location end);

        Entity* entity(int entityID);
        Entity* entityAt(Location location);
        bool entityExists(int entityID);
        bool entityExistsAt(Location location);
        Entity* createEntity(EntityType type, Location location);
        void destroyEntity(int entityID);

        Area* area(){return _area;}
        const Area* area() const{return _area;}
        std::map<int, std::shared_ptr<Entity>>& entities(){return _entities;}
        const std::map<int, std::shared_ptr<Entity>>& entities() const{return _entities;}
    private:
        Area* _area;
        std::map<int, std::shared_ptr<Entity>> _entities;
};