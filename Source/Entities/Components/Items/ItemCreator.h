#pragma once
#include "Item.h"
//#define generateItem() ItemCreator::instance().generate()

class ItemCreator{
    public:
        ItemCreator(){}
        ~ItemCreator(){}
        ItemCreator(ItemCreator& other) = delete;
        void operator=(const ItemCreator& other) = delete;

        static ItemCreator& instance();
        //Item generate();
    private:

};