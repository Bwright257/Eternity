#include "EquipmentComponent.h"
#include "InventoryComponent.h"
#include "Entity.h"

void EquipmentComponent::equip(Item& item){
    if (item.hasModule(MODULE_EQUIPMENT)){
        EquipmentSlot slot = item.getModule<EquipmentModule>(MODULE_EQUIPMENT)->slot();

        if (isSlotEquipped(slot)){
            unequip(slot);
        }

        _equipment.emplace(slot, item);
        owner()->getComponent<InventoryComponent>(COMP_INVENTORY)->removeFromInventory(item, 1);
    }

    return;
}

void EquipmentComponent::unequip(EquipmentSlot slot){
    if (isSlotEquipped(slot)){
        owner()->getComponent<InventoryComponent>(COMP_INVENTORY)->addToInventory(Slot(*equipmentOnSlot(slot), 1));
        _equipment.erase(slot);
    }

    return;
}

bool EquipmentComponent::isSlotEquipped(EquipmentSlot slot){
    return _equipment.count(slot) > 0;
}

Item* EquipmentComponent::equipmentOnSlot(EquipmentSlot slot){
    if (_equipment.find(slot) != _equipment.end()){
        return &_equipment.find(slot)->second;
    }

    return nullptr;
}