#pragma once
#include <set>
#include "ItemModule.h"
#include "Quest.h"

class QuestModule : public ItemModule{
    public:
        QuestModule() : ItemModule(MODULE_QUEST){}
        ~QuestModule(){}

        
    private:
        std::set<Quest> _quests;
};