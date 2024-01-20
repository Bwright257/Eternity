#pragma once
#include "ItemModule.h"
#include "Upgrades.h"
#include "Stats.h"

typedef enum{ESLOT_WEAPON, ESLOT_HEAD, ESLOT_CHEST, ESLOT_LEGS, ESLOT_HANDS, ESLOT_FEET, ESLOT_NECK, ESLOT_TRINKET, ESLOT_RINGL, ESLOT_RINGR} EquipmentSlot;
typedef enum{WEAPON_DAGGER, WEAPON_SHORTSWORD, WEAPON_SWORD, WEAPON_GREATSWORD, WEAPON_RAPIER, WEAPON_SCIMITAR, WEAPON_AXE, WEAPON_GREATAXE, WEAPON_MACE, WEAPON_WARHAMMER, WEAPON_FLAIL, WEAPON_SPEAR, WEAPON_HALBERD, WEAPON_SCYTHE, WEAPON_NONE} WeaponType;
typedef enum{TIER_RUSTED, TIER_BRASS, TIER_TIN, TIER_COPPER, TIER_BRONZE, TIER_IRON, TIER_STEEL, TIER_MITHRIL, TIER_ORICHALCUM, TIER_ADAMANTITE, TIER_OBSIDIAN, TIER_STORMSILVER, TIER_VOIDSTONE, TIER_AETHERIUM, TIER_ELDERSTEEL} ItemTier;

class EquipmentModule : public ItemModule{
    public:
        EquipmentModule(EquipmentSlot slot, WeaponType weaponType, ItemTier tier, Stats stats, Upgrades upgrades) : ItemModule(MODULE_EQUIPMENT), _slot(slot), _weaponType(weaponType), _tier(tier), _stats(stats), _upgrades(upgrades){}
        virtual ~EquipmentModule(){}

        EquipmentSlot& slot(){return _slot;}
        const EquipmentSlot& slot() const{return _slot;}
        WeaponType& weaponType(){return _weaponType;}
        const WeaponType& weaponType() const{return _weaponType;}
        ItemTier& tier(){return _tier;}
        const ItemTier& tier() const{return _tier;}
        Stats& stats(){return _stats;}
        const Stats& stats() const{return _stats;}
        Upgrades& upgradeModule(){return _upgrades;}
    private:
        EquipmentSlot _slot;
        WeaponType _weaponType;
        ItemTier _tier;
        Stats _stats;
        Upgrades _upgrades;
};