#pragma once
#include <memory>
#include <map>
#include "TitleWidget.h"
#include "LoadSaveWidget.h"
#include "NewGameWidget.h"
#include "SettingsWidget.h"
#include "AreaWidget.h"
#include "PauseWidget.h"

class GameHandler;
class Renderer{
    public:
        Renderer(GameHandler* game) : _game(game), _windowSize(Location(45, 130)){}
        ~Renderer(){}

        void display();
        void init();
        void exit();

        void transmuteWidget(WidgetType oldWidget, WidgetType newWidget);
        void createWidget(WidgetType type);
        void focusWidget(WidgetType type);
        void destroyWidget(WidgetType type);
        Widget* widget(WidgetType type);
        Widget* focusedWidget();

        template <class T>
        T* widget(WidgetType type){
            if (_widgets.find(type) != _widgets.end()){
                return dynamic_cast<T*>(_widgets.find(type)->second.get());
            }

            return nullptr;
        }

        GameHandler* game(){return _game;}
        const GameHandler* game() const{return _game;}
        Location& windowSize(){return _windowSize;}
        const Location& windowSize() const{return _windowSize;}
        Location& mouseLocation(){return _mouseLocation;}
        const Location& mouseLocation() const{return _mouseLocation;}
        WidgetType& focusedWidgetType(){return _focusedWidgetType;}
        const WidgetType& focusedWidgetType() const{return _focusedWidgetType;}
    private:
        GameHandler* _game;
        Location _windowSize;
        Location _mouseLocation;
        WidgetType _focusedWidgetType;
        std::map<WidgetType, std::shared_ptr<Widget>> _widgets;
};