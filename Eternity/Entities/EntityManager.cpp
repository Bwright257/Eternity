#include "EntityManager.h"
#include "Slate.h"

void EntityManager::moveEntity(int entityID, Direction direction){
    Location destination = directionalLocation(entity(entityID)->location(), direction);

    if (slate()->world().tileAt(destination) == TILE_GROUND && !entityExistsAt(destination)){
        entity(entityID)->location() = destination;
    } else {
        std::vector<Location> outputs;
        std::vector<Direction> subDirections;

        if (direction == DIR_NORTH || direction == DIR_SOUTH){
            subDirections = {DIR_WEST, DIR_EAST};
        } else {
            subDirections = {DIR_NORTH, DIR_SOUTH};
        }

        for (auto & subDir : subDirections){
            Location subLoc = directionalLocation(entity(entityID)->location(), subDir);

            if (slate()->world().tileAt(subLoc) == TILE_GROUND && !entityExistsAt(subLoc)){
                Location output = directionalLocation(entity(entityID)->location(), addDirections(direction, subDir));

                if (slate()->world().tileAt(output) == TILE_GROUND && !entityExistsAt(output)){
                    outputs.push_back(output);
                }
            }
        }

        if (!outputs.empty()){
            entity(entityID)->location() = outputs[rand() % outputs.size()];
        }
    }

    return;
}

Entity* EntityManager::entity(int entityID){
    if (_entities.find(entityID) != _entities.end()){
        return _entities.find(entityID)->second.get();
    }

    return nullptr;
}

Entity* EntityManager::entityAt(Location location){
    for (auto & entityID : entities()){
        if (entity(entityID.first)->location() == location){
            return entity(entityID.first);
        }
    }

    return nullptr;
}

bool EntityManager::entityExists(int entityID){
    return _entities.count(entityID) > 0;
}

bool EntityManager::entityExistsAt(Location location){
    for (auto & entityID : _entities){
        if (entity(entityID.first)->location() == location){
            return true;
        }
    }

    return false;
}

Entity* EntityManager::createEntity(EntityType type, Location location){
    int entityID = 0;
    _entities.emplace(entityID, std::make_shared<Entity>(entityID, type, location));
    return entity(entityID);
}

void EntityManager::destroyEntity(int entityID){
    if (entityExists(entityID)){
        _entities.erase(entityID);
    }

    return;
}