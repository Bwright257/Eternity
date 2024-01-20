#pragma once
#include <BearLibTerminal.h>
#include "Location.h"
#include "Menu.h"

typedef enum{WIDGET_TITLE, WIDGET_LOADSAVE, WIDGET_NEWGAME, WIDGET_SETTINGS, WIDGET_AREA, WIDGET_PAUSE} WidgetType;

class Renderer;
class Widget{
    public:
        Widget(Renderer* renderer, WidgetType type, Location origin = Location(0, 0), Location size = Location(0, 0)) : _renderer(renderer), _type(type), _origin(origin), _size(size){}
        virtual ~Widget(){}

        void drawBorder(Location origin, Location size);
        virtual void display() = 0;
        virtual bool receiveInput(int input) = 0;
        virtual void receiveFocus() = 0;
        virtual void loseFocus() = 0;

        void autoSize(Menu menu);
        void alignOrigin(int horiAlign, int vertAlign);

        Renderer* renderer(){return _renderer;}
        const Renderer* renderer() const{return _renderer;}
        WidgetType& type(){return _type;}
        const WidgetType& type() const{return _type;}
        Location& origin(){return _origin;}
        const Location& origin() const{return _origin;}
        Location& size(){return _size;}
        const Location& size() const{return _size;}
    private:
        Renderer* _renderer;
        WidgetType _type;
        Location _origin;
        Location _size;
};