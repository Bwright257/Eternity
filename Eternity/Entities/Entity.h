#pragma once
#include <memory>
#include "Location.h"
#include "EquipmentComponent.h"
#include "InteractiveComponent.h"
#include "InventoryComponent.h"
#include "LevelingComponent.h"
#include "StatsComponent.h"

typedef enum{ENTITY_PLAYER = '@', ENTITY_SKELETON = 'S', ENTITY_CHEST = 'C'} EntityType;

class Entity{
    public:
        Entity(int entityID, EntityType type, Location location);
        ~Entity(){}

        template <class T>
        T* getComponent(ComponentType type){
            if (_components.find(type) != _components.end()){
                return dynamic_cast<T*>(_components.find(type)->second.get());
            }
            
            return nullptr;
        }

        void createComponent(ComponentType type);
        void createComponents(std::vector<ComponentType> types);
        void destroyComponent(ComponentType type);
        void destroyComponents(std::vector<ComponentType> types);
        bool hasComponent(ComponentType type);
        bool hasComponents(std::vector<ComponentType> types);

        const int& entityID() const{return _entityID;}
        EntityType& type(){return _type;}
        const EntityType& type() const{return _type;}
        Location& location(){return _location;}
        const Location location() const{return _location;}
    private:
        const int _entityID;
        EntityType _type;
        Location _location;
        std::map<ComponentType, std::shared_ptr<Component>> _components;
};