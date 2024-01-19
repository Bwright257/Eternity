#pragma once
#include <vector>
#include "Light.h"

class Lightmask{
    public:
        Lightmask(){}
        ~Lightmask(){}


    private:
        std::vector<Light> _lights;
};