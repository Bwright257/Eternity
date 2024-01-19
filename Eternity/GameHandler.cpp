#include "GameHandler.h"

void GameHandler::run(){
    while (_isRunning){
        _isRunning = handleInput();
        renderer().display();
    }

    return;
}
#include <iostream>
bool GameHandler::handleInput(){
    bool keepRunning{true};
    renderer().mouseLocation() = Location(terminal_state(TK_MOUSE_Y), terminal_state(TK_MOUSE_X));
    
    while (terminal_has_input()){
        int input = terminal_read();

        if (renderer().focusedWidget() != nullptr){
            keepRunning = renderer().focusedWidget()->receiveInput(input);
        }
    }

    return keepRunning;
}

void GameHandler::startGame(){
    createSlate();
    createPlayer();
    return;
}

void GameHandler::resetGame(){
    _slates.clear();
    return;
}

Entity* GameHandler::player(){
    return entityManager().entity(_playerID);
}

void GameHandler::createPlayer(){
    _playerID = entityManager().createEntity(ENTITY_PLAYER, Location(0, 0))->entityID();
    return;
}

void GameHandler::movePlayer(Direction direction){
    Location oldRegion = world().worldToLocal(player()->location()).regionLocation();
    entityManager().moveEntity(player()->entityID(), direction);

    Location newRegion = world().worldToLocal(player()->location()).regionLocation();
    if (oldRegion != newRegion){
        world().update(player()->location());
    }

    return;
}

World& GameHandler::world(){
    return slate(_activeSlateID)->world();
}

EntityManager& GameHandler::entityManager(){
    return slate(_activeSlateID)->entityManager();
}

Slate* GameHandler::slate(int slateID){
    if (_slates.find(slateID) != _slates.end()){
        return _slates.find(slateID)->second.get();
    }

    return nullptr;
}

void GameHandler::createSlate(){
    _activeSlateID = 0;
    _slates.emplace(_activeSlateID, std::make_shared<Slate>());
    return;
}

void GameHandler::destroySlate(int slateID){
    _slates.erase(slateID);
    return;
}