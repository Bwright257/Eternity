#include "InventoryComponent.h"

void InventoryComponent::addToInventory(Slot slot){
    int index = indexOf(slot.item());

    if (slot.item().isStackable()){
        if (index != -1){
            slotAt(index)->count() += slot.count();
        } else {
            _inventory.push_back(slot);
        }
    } else {
        for (int i = 0; i < slot.count(); i++){
            _inventory.push_back(Slot(slot.item(), 1));
        }
    }

    return;
}

void InventoryComponent::removeFromInventory(Item& item, int count){
    int index = indexOf(item);

    if (index != -1){
        if (item.isStackable()){
            slotAt(index)->count() -= count;

            if (slotAt(index)->count() <= 0){
                _inventory.erase(_inventory.begin() + index);
            }
        } else {
            _inventory.erase(_inventory.begin() + index);

            for (int i = 1; i < count; i++){
                index = indexOf(item);

                if (index != -1){
                    _inventory.erase(_inventory.begin() + index);
                }
            }
        }
    }

    return;
}

size_t InventoryComponent::indexOf(Item& item){
    for (size_t i = 0; i < _inventory.size(); i++){
        if (slotAt(i)->item() == item){
            return i;
        }
    }

    return -1;
}

Slot* InventoryComponent::slotAt(size_t index){
    if (index < _inventory.size()){
        return &_inventory[index];
    }

    return nullptr;
}