#include <cstdlib>
#include "Region.h"

Region::Region(int size) : _isComplete(false){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            createTile(Location(i, j), rand() % 2 == 0 ? TILE_WALL : TILE_GROUND);
        }
    }

    return;
}

Region::Region(std::map<Location, Tile> tiles) : _isComplete(true){
    _tiles = tiles;
    return;
}

Tile& Region::tileAt(Location localLocation){
    return _tiles.find(localLocation)->second;
}

void Region::createTile(Location localLocation, Tile tile){
    _tiles.emplace(localLocation, tile);
    return;
}

void Region::destroyTile(Location localLocation){
    if (tileExistsAt(localLocation)){
        _tiles.erase(localLocation);
    }
    
    return;
}

bool Region::tileExistsAt(Location localLocation){
    return _tiles.count(localLocation) > 0;
}