#pragma once
#include <string>
#include "ItemModule.h"

class LoreModule : public ItemModule{
    public:
        LoreModule(std::string lore) : ItemModule(MODULE_LORE), _lore(lore){}
        ~LoreModule(){}

        std::string& lore(){return _lore;}
        const std::string& lore() const{return _lore;}
    private:
        std::string _lore;
};