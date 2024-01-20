#pragma once

typedef enum{COMP_AI, COMP_EQUIPMENT, COMP_INTERACTIVE, COMP_INVENTORY, COMP_LEVELING, COMP_STATS} ComponentType;

class Entity;
class Component{
    public:
        Component(Entity* owner, ComponentType type) : _owner(owner), _type(type){}
        virtual ~Component(){_owner = nullptr;}

        Entity* owner(){return _owner;}
        const Entity* owner() const{return _owner;}
        ComponentType& type(){return _type;}
        const ComponentType& type() const{return _type;}
    private:
        Entity* _owner;
        ComponentType _type;
};