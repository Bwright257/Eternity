#include "Stats.h"

Stats::Stats(){
    for (int i = S_DAMAGE; i != S_LAST; i++){
        statValue(static_cast<Stat>(i)) = 0;
    }

    return;
}

Stats& Stats::operator+=(const Stats& stats){
    for (int i = S_DAMAGE; i != S_LAST; i++){
        statValue(static_cast<Stat>(i)) += stats.statValue(static_cast<Stat>(i));
    }

    return *this;
}