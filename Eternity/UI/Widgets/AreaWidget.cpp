#include "AreaWidget.h"
#include "GameHandler.h"

AreaWidget::AreaWidget(Renderer* renderer) : Widget(renderer, WIDGET_AREA, Location(0, 0), Location(35, 105)){
    alignOrigin(TK_ALIGN_LEFT, TK_ALIGN_TOP);
    return;
}

void AreaWidget::display(){
    drawBorder(origin(), size());

    Location renderOffset = origin() + (size() / 2) - renderer()->game()->player()->location();
    Location minRender = origin() + Location(1, 1) - renderOffset;
    Location maxRender = origin() + size() - Location(2, 2) - renderOffset;

    for (int i = minRender.row(); i <= maxRender.row(); i++){
        for (int j = minRender.column(); j <= maxRender.column(); j++){
            Location worldLocation = Location(i, j);
            Location screenLocation = worldLocation + renderOffset;

            if (renderer()->game()->area()->tileExistsAt(worldLocation)){
                terminal_put(screenLocation.column(), screenLocation.row(), char(renderer()->game()->area()->tileAt(worldLocation)));
            }
        }
    }
    
    for (auto & entityID : renderer()->game()->slate(renderer()->game()->activeSlateID())->entityManager().entities()){
        Entity* entity = entityID.second.get();
        Location renderLocation = entity->location() + renderOffset;

        if (entity->location() >= minRender && entity->location() <= maxRender){
            terminal_put(renderLocation.column(), renderLocation.row(), char(entity->type()));
        }
    }

    return;
}

bool AreaWidget::receiveInput(int input){
    GameHandler* game = renderer()->game();

    switch (input){
        case TK_UP:
        case TK_W:
            game->movePlayer(DIR_NORTH);
            break;
        case TK_LEFT:
        case TK_A:
            game->movePlayer(DIR_WEST);
            break;
        case TK_DOWN:
        case TK_S:
            game->movePlayer(DIR_SOUTH);
            break;
        case TK_RIGHT:
        case TK_D:
            game->movePlayer(DIR_EAST);
            break;
        case TK_ESCAPE:
        case TK_CLOSE:
            renderer()->transmuteWidget(type(), WIDGET_PAUSE);
            break;
    }

    return true;
}

void AreaWidget::receiveFocus(){
    return;
}

void AreaWidget::loseFocus(){
    return;
}