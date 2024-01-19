#pragma once
#include "Component.h"

class InteractiveComponent : public Component{
    public:
        InteractiveComponent(Entity* owner) : Component(owner, COMP_INTERACTIVE){}
        ~InteractiveComponent(){}

        
    private:

};