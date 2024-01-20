#pragma once
#include <vector>
#include <string>
#include "WidgetObject.h"

class Menu : public WidgetObject{
    public:
        Menu(std::vector<std::string> choices = {});
        ~Menu(){}

        void display(Location origin, Location size, int horiAlign, int vertAlign);

        void incrementSelection();
        void decrementSelection();

        size_t firstAvailableChoice(size_t selection, bool forwards);

        void enableChoice(size_t selection);
        void disableChoice(size_t selection);
        bool isEnabled(size_t selection);

        size_t& selection(){return _selection;}
        const size_t& selection() const{return _selection;}
        std::vector<std::string>& choices(){return _choices;}
        const std::vector<std::string>& choices() const{return _choices;}
        std::vector<bool>& enabledStatus(){return _enabledStatus;}
        const std::vector<bool>& enabledStatus() const{return _enabledStatus;}
    private:
        size_t _selection;
        std::vector<std::string> _choices;
        std::vector<bool> _enabledStatus;
};