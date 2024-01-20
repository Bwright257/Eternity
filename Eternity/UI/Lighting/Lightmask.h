#pragma once
#include <vector>
#include <map>
#include "Light.h"

class Lightmask{
    public:
        Lightmask(){}
        ~Lightmask(){}

        std::map<Location, color_t> calcLighting(Location minLocation, Location maxLocation);
    private:
        std::vector<Light> _lights;
};