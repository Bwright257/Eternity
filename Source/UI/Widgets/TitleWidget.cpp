#include "TitleWidget.h"
#include "GameHandler.h"
#include "Saver.h"

TitleWidget::TitleWidget(Renderer* renderer) : Widget(renderer, WIDGET_TITLE), _title("Eternity", true), _menu({"Continue", "Load", "New Game", "Settings", "Quit"}){
    autoSize(menu());
    alignOrigin(TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);

    if (saver.meta().lastSave() == -1){
        //menu().disableChoice(0);
    }

    return;
}

void TitleWidget::display(){
    title().display(origin() - Location(1, 0), size(), TK_ALIGN_CENTER, TK_ALIGN_TOP);
    menu().display(origin(), size(), TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

bool TitleWidget::receiveInput(int input){
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
                    renderer()->game()->startGame();
                    renderer()->transmuteWidget(type(), WIDGET_AREA);
                    break;
                case 1:
                    renderer()->transmuteWidget(type(), WIDGET_LOADSAVE);
                    break;
                case 2:
                    renderer()->transmuteWidget(type(), WIDGET_NEWGAME);
                    break;
                case 3:
                    renderer()->transmuteWidget(type(), WIDGET_SETTINGS);
                    break;
                case 4:
                    return false;
                    break;
                default:
                    break;
            }

            break;
        case TK_ESCAPE:
        case TK_CLOSE:
            return false;
            break;
    }

    return true;
}

void TitleWidget::receiveFocus(){
    menu().selection() = menu().firstAvailableChoice(0, true);
    return;
}

void TitleWidget::loseFocus(){
    menu().selection() = -1;
    return;
}