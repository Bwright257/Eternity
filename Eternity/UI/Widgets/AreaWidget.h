#pragma once
#include "Widget.h"
#include "World.h"

class AreaWidget : public Widget{
    public:
        AreaWidget(Renderer* renderer);
        ~AreaWidget(){}

        void display();
        bool receiveInput(int input);
        void receiveFocus();
        void loseFocus();
    private:
};