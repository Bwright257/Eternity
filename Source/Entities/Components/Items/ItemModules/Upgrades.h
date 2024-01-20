#pragma once
#include "ItemModule.h"

class Upgrades{
    public:
        Upgrades(int upgradeTier) : _upgradeTier(upgradeTier), _maxTier(15){}
        ~Upgrades(){}

        void upgrade();
        bool canUpgrade();

        int& upgradeTier(){return _upgradeTier;}
        const int& upgradeTier() const{return _upgradeTier;}
    private:
        int _upgradeTier;
        const int _maxTier;
};