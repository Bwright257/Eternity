#pragma once
#include <map>
#include "Light.h"
#include "Tile.h"

class Lightmask{
    public:
        Lightmask(){}
        ~Lightmask(){}

        void createLight(Location source, color_t color, float intensity, float range);
        void destroyLight(int lightID);

        std::map<Location, color_t> calcLighting(std::map<Location, Tile>& tiles);
    private:
        std::map<int, Light> _lights;
};