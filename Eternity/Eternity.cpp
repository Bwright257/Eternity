#include "GameHandler.h"

int main(){
    GameHandler game;
    game.renderer().init();

    game.renderer().createWidget(WIDGET_TITLE);
    game.renderer().focusWidget(WIDGET_TITLE);
    game.run();
    
    game.renderer().exit();
    return 0;
}