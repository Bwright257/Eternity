#include <cmath>
#include "LevelingComponent.h"

int LevelingComponent::level(){
    return trunc(sqrt(double(_experience) / 10.0) + 1);
}

void LevelingComponent::addExperience(int experience){
    _experience += experience;
    return;
}

void LevelingComponent::removeExperience(int experience){
    _experience -= experience;

    if (_experience < 0){
        _experience = 0;
    }

    return;
}