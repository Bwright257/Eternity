#include <filesystem>
#include <fstream>
#include <vector>
#include <cmath>
#include "World.h"

World::World(int seed) : Area(seed), _regionSize(35), _activeRegion(Location(0, 0)), _loadDistance(Location(1, 2)){
    init();
    for (auto & file : std::filesystem::directory_iterator("Data/Regions")){
        std::filesystem::remove_all(file.path());
    }
    
    return;
}

World::~World(){
    for (auto & file : std::filesystem::directory_iterator("Data/Regions")){
        std::filesystem::remove_all(file.path());
    }
    
    return;
}

void World::init(){
    std::set<Location> locations;

    for (int i = -3; i <= 3; i++){
        for (int j = -3; j <= 3; j++){
            generateRegion(Location(i, j));
            locations.insert(Location(i, j));
        }
    }

    smoothRegions(locations);
    return;
}

void World::update(Location worldLocation){
    _activeRegion = worldToLocal(worldLocation).regionLocation();

    std::set<Location> unloadLocations = regionsToUnload();
    saveRegions(unloadLocations);
    unloadRegions(unloadLocations);

    std::set<Location> loadLocations = regionsToLoad();
    std::set<Location> generatedLocations;

    for (auto & regionLocation : loadLocations){
        if (!regionExistsAt(regionLocation)){
            if (isRegionSaved(regionLocation)){
                loadRegion(regionLocation);
            } else {
                generateRegion(regionLocation);
                generatedLocations.insert(regionLocation);
            }
        }
    }

    if (!generatedLocations.empty()){
        smoothRegions(generatedLocations);
    }

    return;
}

void World::generateRegion(Location regionLocation){
    regions().emplace(regionLocation, std::make_shared<Region>(_regionSize));
    return;
}

void World::generateRegions(std::set<Location> regionLocations){
    for (auto & regionLocation : regionLocations){
        generateRegion(regionLocation);
    }

    return;
}

void World::smoothRegions(std::set<Location> regionLocations){
    std::set<Location> smoothedRegions;
    const int cycles{10};
    
    for (int c = 0; c < cycles; c++){
        std::map<Location, Tile> tiles;

        for (auto & regionLocation : regionLocations){
            if (regionExistsAt(regionLocation) && !regionAt(regionLocation)->isComplete()){
                smoothedRegions.insert(regionLocation);

                for (auto & tile : regionAt(regionLocation)->tiles()){
                    Location tileLocation = localToWorld(RelativeLocation(regionLocation, tile.first));
                    tiles.emplace(tileLocation, tile.second);
                }
            }
        }
        
        for (auto & tile : tiles){
            if (tileExistsAt(tile.first)){
                int wallCount = numSurroundingWalls(tile.first);

                if (tileAt(tile.first) == TILE_GROUND && wallCount >= 5){
                    tile.second = TILE_WALL;
                } else if (tileAt(tile.first) == TILE_WALL && wallCount < 4){
                    tile.second = TILE_GROUND;
                }
            }
        }

        for (auto & tile : tiles){
            if (tileExistsAt(tile.first)){
                tileAt(tile.first) = tile.second;
            }
        }
    }

    for (auto & regionLocation : smoothedRegions){
        regionAt(regionLocation)->isComplete() = true;
    }

    return;
}

void World::saveRegion(Location regionLocation){
    std::ofstream outFile;
    outFile.open(pathToRegion(regionLocation), std::ostream::trunc);

    for (auto & tile : regionAt(regionLocation)->tiles()){
        outFile << std::to_string(tile.first.row()) + " " + std::to_string(tile.first.column()) + " " + std::to_string(tile.second) + " ";
    }

    outFile.close();
    return;
}

void World::saveRegions(std::set<Location> regionLocations){
    for (auto & regionLocation : regionLocations){
        saveRegion(regionLocation);
    }

    return;
}

void World::loadRegion(Location regionLocation){
    std::string path = pathToRegion(regionLocation);

    if (isRegionSaved(regionLocation)){
        std::ifstream inFile;
        inFile.open(path);

        std::map<Location, Tile> tiles;
        std::string row, column, type;

        while (inFile.good()){
            inFile >> row;
            inFile >> column;
            inFile >> type;
            tiles.emplace(Location(std::stoi(row), std::stoi(column)), static_cast<Tile>(std::stoi(type)));
        }

        regions().emplace(regionLocation, std::make_shared<Region>(tiles));
        inFile.close();
    }

    return;
}

void World::loadRegions(std::set<Location> regionLocations){
    for (auto & regionLocation : regionLocations){
        loadRegion(regionLocation);
    }

    return;
}

void World::unloadRegion(Location regionLocation){
    regions().erase(regionLocation);
    return;
}

void World::unloadRegions(std::set<Location> regionLocations){
    for (auto & regionLocation : regionLocations){
        unloadRegion(regionLocation);
    }

    return;
}

bool World::isRegionSaved(Location regionLocation){
    return std::filesystem::exists(pathToRegion(regionLocation));
}

std::string World::pathToRegion(Location regionLocation){
    return "Data/Regions/(" + std::to_string(regionLocation.row()) + "," + std::to_string(regionLocation.column()) + ")";
}

std::set<Location> World::regionsToLoad(){
    std::set<Location> regionLocations;

    for (int i = _activeRegion.row() - _loadDistance.row(); i <= _activeRegion.row() + _loadDistance.row(); i++){
        for (int j = _activeRegion.column() - _loadDistance.column(); j <= _activeRegion.column() + _loadDistance.column(); j++){
            regionLocations.insert(Location(i, j));
        }
    }

    return regionLocations;
}

std::set<Location> World::regionsToUnload(){
    std::set<Location> regionLocations;

    for (auto & region : regions()){
        regionLocations.insert(region.first);
    }

    for (auto & regionLocation : regionsToLoad()){
        regionLocations.erase(regionLocation);
    }

    return regionLocations;
}

int World::numAdjacentWalls(Location worldLocation){
    int count{0};
    std::vector<Direction> adjacents = {DIR_NORTH, DIR_WEST, DIR_SOUTH, DIR_EAST};

    for (auto & adjacent : adjacents){
        Location target = directionalLocation(worldLocation, adjacent);

        if (tileExistsAt(target) && tileAt(target) == TILE_WALL){
            count++;
        }
    }

    return count;
}

int World::numSurroundingWalls(Location worldLocation){
    int count{0};
    std::vector<Direction> surroundings = {DIR_NORTH, DIR_WEST, DIR_SOUTH, DIR_EAST, DIR_NORTHEAST, DIR_NORTHWEST, DIR_SOUTHWEST, DIR_SOUTHEAST};

    for (auto & surrounding : surroundings){
        Location target = directionalLocation(worldLocation, surrounding);

        if (tileExistsAt(target)){
            if (tileAt(target) == TILE_WALL){
                count++;
            }
        } else {
            if (rand() % 2 == 0){
                count++;
            }
        }
    }

    return count;
}

Location World::localToWorld(RelativeLocation relativeLocation){
    return relativeLocation.localLocation() + (relativeLocation.regionLocation() * _regionSize);
}

RelativeLocation World::worldToLocal(Location worldLocation){
    Location regionLocation = Location(floor(double(worldLocation.row()) / double(_regionSize)), floor(double(worldLocation.column()) / double(_regionSize)));
    Location localLocation = (regionLocation * -_regionSize) + worldLocation;
    return RelativeLocation(regionLocation, localLocation);
}

Tile& World::tileAt(Location worldLocation){
    return tileAt(worldToLocal(worldLocation));
}

Tile& World::tileAt(RelativeLocation relativeLocation){
    return regionAt(relativeLocation.regionLocation())->tileAt(relativeLocation.localLocation());
}

bool World::tileExistsAt(Location worldLocation){
    return tileExistsAt(worldToLocal(worldLocation));
}

bool World::tileExistsAt(RelativeLocation relativeLocation){
    if (regionExistsAt(relativeLocation.regionLocation())){
        return regionAt(relativeLocation.regionLocation())->tileExistsAt(relativeLocation.localLocation());
    }

    return false;
}

Region* World::regionAt(Location regionLocation){
    if (_regions.find(regionLocation) != _regions.end()){
        return _regions.find(regionLocation)->second.get();
    }

    return nullptr;
}

bool World::regionExistsAt(Location regionLocation){
    return _regions.count(regionLocation) > 0;
}