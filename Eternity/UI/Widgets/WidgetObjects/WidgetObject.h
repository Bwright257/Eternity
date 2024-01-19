#pragma once
#include <BearLibTerminal.h>
#include "Location.h"

class WidgetObject{
    public:
        WidgetObject(){}
        virtual ~WidgetObject(){}

        virtual void display(Location origin, Location size, int horiAlign, int vertAlign) = 0;
    private:

};