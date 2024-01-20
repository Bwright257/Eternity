#pragma once
#include "Component.h"
#include "Item.h"

struct Slot{
    public:
        Slot(Item item, int count) : _item(item), _count(count){}
        ~Slot(){}

        Item& item(){return _item;}
        int& count(){return _count;}
    private:
        Item _item;
        int _count;
};

class InventoryComponent : public Component{
    public:
        InventoryComponent(Entity* owner) : Component(owner, COMP_INVENTORY){}
        ~InventoryComponent(){}

        void addToInventory(Slot slot);
        void removeFromInventory(Item& item, int count);
        size_t indexOf(Item& item);
        Slot* slotAt(size_t index);

        std::vector<Slot>& inventory(){return _inventory;}
        const std::vector<Slot>& inventory() const{return _inventory;}
    private:
        std::vector<Slot> _inventory;
};