#pragma once
#include "Renderer.h"
#include "Slate.h"

class GameHandler{
    public:
        GameHandler() : _isRunning(true), _isPaused(false), _tickRate(500), _renderer(this){}
        ~GameHandler(){}

        void run();
        void tick();
        bool handleInput();

        void startGame();
        void resetGame();

        Entity* player();
        void createPlayer();
        void movePlayer(Direction direction);
        void moveSlate(int slateID);

        Area* area();
        EntityManager* entityManager();

        Slate* slate(int slateID);
        void createSlate(std::shared_ptr<Area> area);
        void destroySlate(int slateID);
        
        bool& isRunning(){return _isRunning;}
        const bool& isRunning() const{return _isRunning;}
        bool& isPaused(){return _isPaused;}
        const bool& isPaused() const{return _isPaused;}
        int& activeSlateID(){return _activeSlateID;}
        const int& activeSlateID() const{return _activeSlateID;}
        Renderer& renderer(){return _renderer;}
        const Renderer& renderer() const{return _renderer;}
    private:
        bool _isRunning;
        bool _isPaused;
        int _tickRate;
        int _playerID;
        int _activeSlateID;
        std::map<int, std::shared_ptr<Slate>> _slates;
        Renderer _renderer;
};