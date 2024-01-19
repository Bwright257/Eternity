#pragma once
#include <map>

typedef enum{S_DAMAGE, S_ARMOR, S_HEALTH, S_MAXHEALTH, S_LAST} Stat;

struct Stats{
    public:
        Stats();
        ~Stats(){}
        Stats& operator+=(const Stats& stats);

        int& statValue(Stat stat){return _stats.find(stat)->second;}
        const int& statValue(Stat stat) const{return _stats.find(stat)->second;}
    private:
        std::map<Stat, int> _stats;
};