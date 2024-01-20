#pragma once
#include "Component.h"
#include "Stats.h"

class StatsComponent : public Component{
    public:
        StatsComponent(Entity* owner) : Component(owner, COMP_STATS){}
        ~StatsComponent(){}

        int heal(int health);
        int takeDamage(int damage);

        int& statValue(Stat stat){return stats().statValue(stat);}
        const int& statValue(Stat stat) const{return stats().statValue(stat);}
        Stats& stats(){return _stats;}
        const Stats& stats() const{return _stats;}
    private:
        Stats _stats;
};