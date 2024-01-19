#pragma once
#include <string>

class MetaSave{
    public:
        MetaSave() : _saveID("meta"), _lastSave(-1){}
        ~MetaSave(){}

        const std::string saveID() const{return _saveID;}
        int& lastSave(){return _lastSave;}
        const int& lastSave() const{return _lastSave;}
    private:
        const std::string _saveID;
        int _lastSave;
};