#pragma once
#include "Component.h"
#include "EquipmentModule.h"
#include "Item.h"

class EquipmentComponent : public Component{
    public:
        EquipmentComponent(Entity* owner) : Component(owner, COMP_EQUIPMENT){}
        ~EquipmentComponent(){}

        void equip(Item& item);
        void unequip(EquipmentSlot slot);
        bool isSlotEquipped(EquipmentSlot slot);
        Item* equipmentOnSlot(EquipmentSlot slot);

        std::map<EquipmentSlot, Item>& equipment(){return _equipment;}
    private:
        std::map<EquipmentSlot, Item> _equipment;
};