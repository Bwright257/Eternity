#pragma once
#include "Component.h"

class AIComponent : public Component{
    public:
        AIComponent(Entity* owner) : Component(owner, COMP_AI){}
        ~AIComponent(){}


    private:

};