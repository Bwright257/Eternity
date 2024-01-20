#pragma once
#include <ctime>
#include "Location.h"
#include "Tile.h"

class Area{
    public:
        Area(int seed = time(NULL));
        virtual ~Area(){}

        virtual Tile& tileAt(Location location) = 0;
        virtual bool tileExistsAt(Location location) = 0;

        int& seed(){return _seed;}
        const int& seed() const{return _seed;}
    private:
        int _seed;
};