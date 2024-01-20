#include "Lightmask.h"

std::map<Location, color_t> Lightmask::calcLighting(Location minLocation, Location maxLocation){
    std::map<Location, color_t> lighting;

    for (int i = minLocation.row(); i <= maxLocation.row(); i++){
        for (int j = maxLocation.column(); j <= maxLocation.column(); j++){
            Location location = Location(i, j);

            
        }
    }

    return lighting;
}