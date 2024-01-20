#include "Item.h"

Item::Item(std::string name, std::string description, bool isStackable, Rarity rarity, std::vector<ModuleType> modules) : _name(name), _description(description), _isStackable(isStackable), _rarity(rarity){
    addModules(modules);
    return;
}

bool Item::operator==(Item& item){
    return _name == item.name();
}

void Item::addModule(ModuleType type){
    std::shared_ptr<ItemModule> module;

    switch (type){
        case MODULE_EQUIPMENT:
            //module = std::make_shared<EquipmentModule>();
            break;
        case MODULE_LORE:
            //module = std::make_shared<LoreModule>();
            break;
        case MODULE_QUEST:
            //module = std::make_shared<QuestModule>();
            break;
        default:
            break;
    }

    if (!hasModule(type)){
        _modules.emplace(type, module);
    }
}

void Item::addModules(std::vector<ModuleType> types){
    for (auto & type : types){
        addModule(type);
    }
}

bool Item::hasModule(ModuleType type){
    return _modules.count(type) > 0;
}

bool Item::hasModules(std::vector<ModuleType> types){
    for (auto & type : types){
        if (!hasModule(type)){
            return false;
        }
    }

    return true;
}