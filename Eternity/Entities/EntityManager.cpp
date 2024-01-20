#include <algorithm>
#include <cmath>
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

Direction EntityManager::directionTo(Location start, Location end){
    Direction direction{DIR_NORTH};

    float pi = atan(1)*4;
    float angle = atan2f(start.column() - end.column(), start.row() - end.row());
    
    if (angle > -pi/4 && angle <= pi/4){
        direction = DIR_NORTH;
    } else if (angle > pi/4 && angle <= 3*pi/4){
        direction = DIR_WEST;
    } else if ((angle > 3*pi/4 && angle <= pi) || (angle >= -pi && angle <= -3*pi/4)){
        direction = DIR_SOUTH;
    } else if (angle > -3*pi/4 && angle <= -pi/4){
        direction = DIR_EAST;
    }

    return direction;
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

    class QueueCompare{
        public:
            bool operator()(std::pair<int, Location> pairOne, std::pair<int, Location> pairTwo){
                return pairOne.first > pairTwo.first;
            }
    };

    std::priority_queue<std::pair<int, Location>, std::vector<std::pair<int, Location>>, QueueCompare> costs;
    costs.push({0, start});

    std::map<Location, int> open = {{start, 0}};
    std::set<Location> closed;
    std::map<Location, Location> cameFrom;

    bool searching = true;
    while (searching && !open.empty()){
        int currentCost = costs.top().first;
        Location currentLoc = costs.top().second;

        costs.pop();
        open.erase(currentLoc);
        closed.insert(currentLoc);

        if (currentLoc == end){
            searching = false;
        } else {
            for (auto & neighbor : adjacentLocations(currentLoc)){
                if (canMoveTo(neighbor) && closed.count(neighbor) == 0){
                    int cost = distanceTo(neighbor, start) + distanceTo(neighbor, end);

                    if (cost < currentCost || open.count(neighbor) == 0){
                        costs.push({cost, neighbor});
                        open.emplace(neighbor, cost);
                        cameFrom[neighbor] = currentLoc;
                    }
                }
            }
        }
    } 

    if (!open.empty()){
        Location current = end;
        while (current != start){
            path.push_back(directionTo(current, cameFrom[current]));
            current = cameFrom[current];
        }
        
        std::reverse(path.begin(), path.end());
        for (auto & direction : path){
            direction = reverseDirection(direction);
        }
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