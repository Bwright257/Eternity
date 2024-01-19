#pragma once
#include <string>
#include "WidgetObject.h"

class Text : public WidgetObject{
    public:
        Text(std::string text, bool isUnderlined) : WidgetObject(), _text(text), _isUnderlined(isUnderlined){}
        ~Text(){}

        void display(Location origin, Location size, int horiAlign, int vertAlign);

        std::string& text(){return _text;}
        const std::string& text() const{return _text;}
        bool& isUnderlined(){return _isUnderlined;}
        const bool& isUnderlined() const{return _isUnderlined;}
    private:
        std::string _text;
        bool _isUnderlined;
};