#include <cstdlib>
#include "Area.h"

Area::Area(int seed) : _seed(seed){
    srand(seed);
    return;
}