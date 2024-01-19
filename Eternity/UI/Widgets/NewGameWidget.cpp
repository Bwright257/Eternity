#include "NewGameWidget.h"
#include "Renderer.h"
#include "Saver.h"

NewGameWidget::NewGameWidget(Renderer* renderer) : Widget(renderer, WIDGET_NEWGAME), _title("Create New Save?", true), _menu({"Create", "Exit"}){
    autoSize(menu());
    alignOrigin(TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    int takenSlots{0};

    for (int i = 0; i < saver.maxSlots(); i++){
        if (saver.saveExists(std::to_string(i))){
            takenSlots++;
        }
    }

    if (takenSlots == saver.maxSlots()){
        menu().disableChoice(0);
    }

    return;
}

void NewGameWidget::display(){
    title().display(origin() - Location(1, 0), size(), TK_ALIGN_CENTER, TK_ALIGN_TOP);
    menu().display(origin(), size(), TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

bool NewGameWidget::receiveInput(int input){
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

                    break;
                case 1:
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

void NewGameWidget::receiveFocus(){
    menu().selection() = menu().firstAvailableChoice(0, true);
    return;
}

void NewGameWidget::loseFocus(){
    menu().selection() = -1;
    return;
}