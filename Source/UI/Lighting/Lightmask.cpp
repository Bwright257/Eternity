#include "Lightmask.h"

void Lightmask::createLight(Location source, color_t color, float intensity, float range){
    static int lightID{-1};
    lightID++;
    _lights.emplace(lightID, Light(lightID, source, color, intensity, range));
    return;
}

void Lightmask::destroyLight(int lightID){
    _lights.erase(lightID);
    return;
}

std::map<Location, color_t> Lightmask::calcLighting(std::map<Location, Tile>& tiles){
    std::map<Location, color_t> lighting;

    

    return lighting;
}