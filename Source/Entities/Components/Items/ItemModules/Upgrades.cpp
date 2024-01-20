#include "Upgrades.h"

void Upgrades::upgrade(){
    if (_upgradeTier < _maxTier){
        _upgradeTier++;
    }

    return;
}

bool Upgrades::canUpgrade(){


    return false;
}