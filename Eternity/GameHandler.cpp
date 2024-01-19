#include <thread>
#include <chrono>
#include "GameHandler.h"

void GameHandler::run(){
    std::thread ticker(tick, this);

    while (_isRunning){
        _isRunning = handleInput();
        renderer().display();
    }

    ticker.join();
    return;
}

void GameHandler::tick(){
    while (_isRunning){
        if (entityManager() != nullptr){
            entityManager()->tick();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(_tickRate));
    }

    return;
}

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
    createSlate(std::make_shared<World>());
    createPlayer();
    return;
}

void GameHandler::resetGame(){
    _slates.clear();
    return;
}

Entity* GameHandler::player(){
    return entityManager()->entity(_playerID);
}

void GameHandler::createPlayer(){
    _playerID = entityManager()->createEntity(ENTITY_PLAYER, Location(0, 0))->entityID();
    return;
}

void GameHandler::movePlayer(Direction direction){
    World* world = dynamic_cast<World*>(area());

    if (world != nullptr){
        Location oldRegion = world->worldToLocal(player()->location()).regionLocation();
        entityManager()->moveEntity(player()->entityID(), direction);

        Location newRegion = world->worldToLocal(player()->location()).regionLocation();
        if (oldRegion != newRegion){
            world->update(player()->location());
        }
    } else {
        entityManager()->moveEntity(player()->entityID(), direction);
    }

    return;
}

Area* GameHandler::area(){
    if (slate(_activeSlateID) != nullptr){
        return slate(_activeSlateID)->area();
    }

    return nullptr;
}

EntityManager* GameHandler::entityManager(){
    if (slate(_activeSlateID) != nullptr){
        return &slate(_activeSlateID)->entityManager();
    }

    return nullptr;
}

Slate* GameHandler::slate(int slateID){
    if (_slates.find(slateID) != _slates.end()){
        return _slates.find(slateID)->second.get();
    }

    return nullptr;
}

void GameHandler::createSlate(std::shared_ptr<Area> area){
    _activeSlateID = 0;
    _slates.emplace(_activeSlateID, std::make_shared<Slate>(std::move(area)));
    return;
}

void GameHandler::destroySlate(int slateID){
    _slates.erase(slateID);
    return;
}