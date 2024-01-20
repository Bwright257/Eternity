#pragma once
#include <map>
#include "Location.h"
#include "Tile.h"

class Region{
    public:
        Region(int size);
        Region(std::map<Location, Tile> tiles);
        ~Region(){}

        Tile& tileAt(Location localLocation);
        void createTile(Location localLocation, Tile tile);
        void destroyTile(Location localLocation);
        bool tileExistsAt(Location localLocation);

        bool& isComplete(){return _isComplete;}
        const bool& isComplete() const{return _isComplete;}
        std::map<Location, Tile>& tiles(){return _tiles;}
        const std::map<Location, Tile>& tiles() const{return _tiles;}
    private:
        bool _isComplete;
        std::map<Location, Tile> _tiles;
};