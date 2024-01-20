#pragma once

typedef enum{MODULE_EQUIPMENT, MODULE_LORE, MODULE_QUEST} ModuleType;

class ItemModule{
    public:
        ItemModule(ModuleType type) : _type(type){}
        virtual ~ItemModule(){}

        ModuleType& type(){return _type;}
        const ModuleType& type() const{return _type;}
    private:
        ModuleType _type;
};