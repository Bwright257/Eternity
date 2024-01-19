#include <BearLibTerminal.h>
#include <Windows.h>
#include "GameHandler.h"
#include "Renderer.h"

void Renderer::display(){
    terminal_clear();

    for (auto & widget : _widgets){
        widget.second->display();
    }

    terminal_refresh();
    return;
}

void Renderer::init(){
    FreeConsole();
    terminal_open();

    terminal_set(std::string{"window.size = " + std::to_string(windowSize().column()) + 'x' + std::to_string(windowSize().row())}.c_str());
    terminal_set("window.title = Eternity");
    terminal_set("window.cellsize = 12x18");
    terminal_set("window.icon: Data/Resources/Eternity.ico");
    terminal_set("font: Data/Resources/Font.ttf, size = 12x24");
    terminal_set("input.filter = {keyboard+, mouse+}");
    terminal_set("input.alt-functions = false");
    terminal_set("output.vsync = false");

    terminal_refresh();
    return;
}

void Renderer::exit(){
    terminal_close();
    return;
}

void Renderer::transmuteWidget(WidgetType oldWidget, WidgetType newWidget){
    createWidget(newWidget);
    focusWidget(newWidget);
    destroyWidget(oldWidget);
    return;
}

void Renderer::createWidget(WidgetType type){
    std::shared_ptr<Widget> widget;

    switch (type){
        case WIDGET_TITLE:
            widget = std::make_shared<TitleWidget>(this);
            break;
        case WIDGET_LOADSAVE:
            widget = std::make_shared<LoadSaveWidget>(this);
            break;
        case WIDGET_NEWGAME:
            widget = std::make_shared<NewGameWidget>(this);
            break;
        case WIDGET_SETTINGS:
            widget = std::make_shared<SettingsWidget>(this);
            break;
        case WIDGET_AREA:
            widget = std::make_shared<AreaWidget>(this);
            break;
        case WIDGET_PAUSE:
            widget = std::make_shared<PauseWidget>(this);
            break;
        default:
            break;
    }

    _widgets.emplace(type, widget);
    return;
}

void Renderer::focusWidget(WidgetType type){
    if (focusedWidgetType() != type){
        if (focusedWidget() != nullptr){
            focusedWidget()->loseFocus();
        }

        focusedWidgetType() = type;
        focusedWidget()->receiveFocus();
    }

    return;
}

void Renderer::destroyWidget(WidgetType type){
    _widgets.erase(type);
    return;
}

Widget* Renderer::widget(WidgetType type){
    return _widgets.find(type)->second.get();
}

Widget* Renderer::focusedWidget(){
    if (_widgets.find(focusedWidgetType()) != _widgets.end()){
        return _widgets.find(focusedWidgetType())->second.get();
    }

    return nullptr;
}