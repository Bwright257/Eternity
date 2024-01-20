#pragma once
#include <string>

class Save{
    public:
        Save(){}
        ~Save(){}

        const std::string saveID() const{return _saveID;}
    private:
        const std::string _saveID;
};