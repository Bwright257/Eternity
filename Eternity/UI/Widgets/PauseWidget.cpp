#include "PauseWidget.h"
#include "GameHandler.h"

PauseWidget::PauseWidget(Renderer* renderer) : Widget(renderer, WIDGET_PAUSE), _title("Paused", false), _menu({"Continue", "Save", "Exit"}){
    this->renderer()->game()->isPaused() = true;
    autoSize(menu());
    alignOrigin(TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

PauseWidget::~PauseWidget(){
    renderer()->game()->isPaused() = false;
    return;
}

void PauseWidget::display(){
    drawBorder(origin(), size());
    title().display(origin() - Location(1, 0), size(), TK_ALIGN_CENTER, TK_ALIGN_TOP);
    menu().display(origin(), size(), TK_ALIGN_CENTER, TK_ALIGN_MIDDLE);
    return;
}

bool PauseWidget::receiveInput(int input){
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
                    renderer()->transmuteWidget(type(), WIDGET_AREA);
                    break;
                case 1:

                    break;
                case 2:
                    renderer()->game()->resetGame();
                    renderer()->transmuteWidget(type(), WIDGET_TITLE);
                    break;
                default:
                    break;
            }

            break;
        case TK_ESCAPE:
        case TK_CLOSE:
            renderer()->transmuteWidget(type(), WIDGET_AREA);
            break;
    }

    return true;
}

void PauseWidget::receiveFocus(){
    menu().selection() = menu().firstAvailableChoice(0, true);
    return;
}

void PauseWidget::loseFocus(){
    menu().selection() = -1;
    return;
}