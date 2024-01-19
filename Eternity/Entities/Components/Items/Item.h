#pragma once
#include <memory>
#include <vector>
#include <map>
#include "EquipmentModule.h"
#include "LoreModule.h"
#include "QuestModule.h"

typedef enum{RARITY_TRASH, RARITY_COMMON, RARITY_UNCOMMON, RARITY_RARE, RARITY_EPIC, RARITY_LEGENDARY, RARITY_MYTHIC, RARITY_UNIQUE} Rarity;

class Item{
    public:
        Item(std::string name, std::string description, bool isStackable, Rarity rarity, std::vector<ModuleType> modules);
        ~Item(){}
        bool operator==(Item& item);

        template <class T>
        T* getModule(ModuleType type){
            if (_modules.find(type) != _modules.end()){
                return dynamic_cast<T*>(_modules.find(type)->second.get());
            }

            return nullptr;
        }

        void addEquipmentModule(EquipmentModule module);
        void addLoreModule(LoreModule module);
        void addQuestModule(QuestModule module);

        void addModule(ModuleType type);
        void addModules(std::vector<ModuleType> types);
        bool hasModule(ModuleType type);
        bool hasModules(std::vector<ModuleType> types);

        std::string& name(){return _name;}
        const std::string& name() const{return _name;}
        std::string& description(){return _description;}
        const std::string& description() const{return _description;}
        bool& isStackable(){return _isStackable;}
        const bool& isStackable() const{return _isStackable;}
        Rarity& rarity(){return _rarity;}
        const Rarity& rarity() const{return _rarity;}
    private:
        std::string _name;
        std::string _description;
        bool _isStackable;
        Rarity _rarity;
        std::map<ModuleType, std::shared_ptr<ItemModule>> _modules;
};