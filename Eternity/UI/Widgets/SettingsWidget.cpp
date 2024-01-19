#include "SettingsWidget.h"
#include "Renderer.h"

SettingsWidget::SettingsWidget(Renderer* renderer) : Widget(renderer, WIDGET_SETTINGS), _title("Settings", true), _menu({"Exit"}){
    autoSize(menu());
    alignOrigin(TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

void SettingsWidget::display(){
    title().display(origin() - Location(1, 0), size(), TK_ALIGN_CENTER, TK_ALIGN_TOP);
    menu().display(origin(), size(), TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

bool SettingsWidget::receiveInput(int input){
    switch (input){
        case TK_UP:
        case TK_W:
            menu().decrementSelection();
            break;
        case TK_DOWN:
        case TK_S:
            menu().incrementSelection();
            break;
        case TK_ENTER:
            switch (menu().selection()){
                case 0:
                    renderer()->transmuteWidget(type(), WIDGET_TITLE);
                    break;
                default:
                    break;
            }
            
            break;
        case TK_ESCAPE:
        case TK_CLOSE:
            renderer()->transmuteWidget(type(), WIDGET_TITLE);
            break;
    }

    return true;
}

void SettingsWidget::receiveFocus(){
    menu().selection() = menu().firstAvailableChoice(0, true);
    return;
}

void SettingsWidget::loseFocus(){
    menu().selection() = -1;
    return;
}