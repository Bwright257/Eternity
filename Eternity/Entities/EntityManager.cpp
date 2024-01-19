#include <queue>
#include "EntityManager.h"
#include "Slate.h"

void EntityManager::tick(){
    for (auto & entity : _entities){
        if (entity.second->hasComponent(COMP_AI)){

        }
    }

    return;
}

void EntityManager::moveEntity(int entityID, Direction direction){
    Location destination = directionalLocation(entity(entityID)->location(), direction);

    if (canMoveTo(destination)){
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

            if (canMoveTo(subLoc)){
                Location output = directionalLocation(entity(entityID)->location(), addDirections(direction, subDir));

                if (canMoveTo(output)){
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

bool EntityManager::canMoveTo(Location location){
    return area()->tileExistsAt(location) && area()->tileAt(location) == TILE_GROUND && !entityExistsAt(location);
}

int EntityManager::distanceTo(Location start, Location end){
    return abs(start.row() - end.row()) + abs(start.column() - end.column());
}

std::set<Location> EntityManager::adjacentLocations(Location location){
    std::set<Location> adjacents;

    for (auto & direction : cardinalDirections()){
        adjacents.insert(directionalLocation(location, direction));
    }

    return adjacents;
}

std::vector<Direction> EntityManager::pathTo(Location start, Location end){
    std::vector<Direction> path;
    std::map<int, Location> locationScores;
    std::priority_queue<int> frontier;

    while (!frontier.empty()){
        frontier.top();

        
    }

    return path;
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