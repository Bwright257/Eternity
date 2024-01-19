#pragma once
#include <memory>
#include <string>
#include <ctime>
#include <set>
#include "Region.h"

class World{
    public:
        World(int seed = time(NULL));
        ~World();

        void init();
        void update(Location worldLocation);

        void generateRegion(Location regionLocation);
        void generateRegions(std::set<Location> regionLocations);
        void smoothRegions(std::set<Location> regionLocations);

        void saveRegion(Location regionLocation);
        void saveRegions(std::set<Location> regionLocations);
        void loadRegion(Location regionLocation);
        void loadRegions(std::set<Location> regionLocations);
        void unloadRegion(Location regionLocation);
        void unloadRegions(std::set<Location> regionLocations);

        bool isRegionSaved(Location regionLocation);
        std::string pathToRegion(Location regionLocation);

        std::set<Location> regionsToLoad();
        std::set<Location> regionsToUnload();

        int numAdjacentWalls(Location worldLocation);
        int numSurroundingWalls(Location worldLocation);

        Location localToWorld(RelativeLocation relativeLocation);
        RelativeLocation worldToLocal(Location worldLocation);

        Tile& tileAt(Location worldLocation);
        Tile& tileAt(RelativeLocation relativeLocation);
        bool tileExistsAt(Location worldLocation);
        bool tileExistsAt(RelativeLocation relativeLocation);

        Region* regionAt(Location regionLocation);
        bool regionExistsAt(Location regionLocation);

        int& seed(){return _seed;}
        const int& seed() const{return _seed;}
        int& regionSize(){return _regionSize;}
        const int& regionSize() const{return _regionSize;}
        Location& activeRegion(){return _activeRegion;}
        const Location& activeRegion() const{return _activeRegion;}
        Location& loadDistance(){return _loadDistance;}
        const Location& loadDistance() const{return _loadDistance;}
        std::map<Location, std::shared_ptr<Region>>& regions(){return _regions;}
        const std::map<Location, std::shared_ptr<Region>>& regions() const{return _regions;}
    private:
        int _seed;
        int _regionSize;
        Location _activeRegion;
        Location _loadDistance;
        std::map<Location, std::shared_ptr<Region>> _regions;
};