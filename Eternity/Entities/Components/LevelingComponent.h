#pragma once
#include "Component.h"

class LevelingComponent : public Component{
    public:
        LevelingComponent(Entity* owner) : Component(owner, COMP_LEVELING){}
        ~LevelingComponent(){}

        int level();
        void addExperience(int experience);
        void removeExperience(int experience);

        int& experience(){return _experience;}
        const int& experience() const{return _experience;}
    private:
        int _experience;
};