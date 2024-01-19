#pragma once
#include "Widget.h"
#include "Text.h"
#include "Menu.h"

class SettingsWidget : public Widget{
    public:
        SettingsWidget(Renderer* renderer);
        ~SettingsWidget(){}

        void display();
        bool receiveInput(int input);
        void receiveFocus();
        void loseFocus();

        Text& title(){return _title;}
        const Text& title() const{return _title;}
        Menu& menu(){return _menu;}
        const Menu& menu() const{return _menu;}
    private:
        Text _title;
        Menu _menu;
};