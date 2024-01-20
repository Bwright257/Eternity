#include "StatsComponent.h"

int StatsComponent::heal(int health){
    int prevHealth{statValue(S_HEALTH)};
    statValue(S_HEALTH) += health;

    if (statValue(S_HEALTH) > statValue(S_MAXHEALTH)){
        statValue(S_HEALTH) = statValue(S_MAXHEALTH);
    }

    return statValue(S_HEALTH) - prevHealth;
}

int StatsComponent::takeDamage(int damage){
    int prevHealth{statValue(S_HEALTH)},
        totalDmg{damage - statValue(S_ARMOR)};

    if (totalDmg < 0){
        totalDmg = 0;
    }

    statValue(S_HEALTH) -= totalDmg;
    return prevHealth - statValue(S_HEALTH);
}