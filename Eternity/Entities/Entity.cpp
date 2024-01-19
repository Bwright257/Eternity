#include "Entity.h"

Entity::Entity(int entityID, EntityType type, Location location) : _entityID(entityID), _type(type), _location(location){
    switch (type){
        case ENTITY_PLAYER:
            createComponents({COMP_EQUIPMENT, COMP_INTERACTIVE, COMP_INVENTORY, COMP_LEVELING, COMP_STATS});
            break;
        case ENTITY_SKELETON:
            createComponents({COMP_AI, COMP_EQUIPMENT, COMP_INVENTORY, COMP_LEVELING, COMP_STATS});
            break;
        case ENTITY_CHEST:
            createComponents({COMP_INTERACTIVE, COMP_INVENTORY});
            break;
        default:
            break;
    }

    return;
}

void Entity::createComponent(ComponentType type){
    std::shared_ptr<Component> comp;

    switch (type){
        case COMP_AI:
            comp = std::make_shared<AIComponent>(this);
            break;
        case COMP_EQUIPMENT:
            comp = std::make_shared<EquipmentComponent>(this);
            break;
        case COMP_INTERACTIVE:
            comp = std::make_shared<InteractiveComponent>(this);
            break;
        case COMP_INVENTORY:
            comp = std::make_shared<InventoryComponent>(this);
            break;
        case COMP_LEVELING:
            comp = std::make_shared<LevelingComponent>(this);
            break;
        case COMP_STATS:
            comp = std::make_shared<StatsComponent>(this);
            break;
        default:
            break;
    }

    _components.emplace(type, comp);
    return;
}

void Entity::createComponents(std::vector<ComponentType> types){
    for (auto & type : types){
        createComponent(type);
    }

    return;
}

void Entity::destroyComponent(ComponentType type){
    _components.erase(type);
    return;
}

void Entity::destroyComponents(std::vector<ComponentType> types){
    for (auto & type : types){
        destroyComponent(type);
    }

    return;
}

bool Entity::hasComponent(ComponentType type){
    return _components.count(type) > 0;
}

bool Entity::hasComponents(std::vector<ComponentType> types){
    for (auto & type : types){
        if (!hasComponent(type)){
            return false;
        }
    }

    return true;
}