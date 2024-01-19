#include "LoadSaveWidget.h"
#include "Renderer.h"
#include "Saver.h"

LoadSaveWidget::LoadSaveWidget(Renderer* renderer) : Widget(renderer, WIDGET_LOADSAVE), _title("Load", true){
    for (int i = 0; i < saver.maxSlots(); i++){
        menu().choices().push_back("Save " + std::to_string(i + 1));
        menu().enabledStatus().push_back(true);
    }

    menu().choices().push_back("Exit");
    menu().enabledStatus().push_back(true);

    for (int i = 0; i < saver.maxSlots(); i++){
        if (!saver.saveExists(std::to_string(i))){
            menu().disableChoice(i);
        }
    }

    autoSize(menu());
    alignOrigin(TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

void LoadSaveWidget::display(){
    title().display(origin() - Location(1, 0), size(), TK_ALIGN_CENTER, TK_ALIGN_TOP);
    menu().display(origin(), size(), TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

bool LoadSaveWidget::receiveInput(int input){
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
            if (int(menu().selection()) < saver.maxSlots()){
                saver.loadSave(std::to_string(menu().selection()));
            } else {
                renderer()->transmuteWidget(type(), WIDGET_TITLE);
            }
            
            break;
        case TK_ESCAPE:
        case TK_CLOSE:
            renderer()->transmuteWidget(type(), WIDGET_TITLE);
            break;
        default:
            break;
    }

    return true;
}

void LoadSaveWidget::receiveFocus(){
    menu().selection() = menu().firstAvailableChoice(0, true);
    return;
}

void LoadSaveWidget::loseFocus(){
    menu().selection() = -1;
    return;
}