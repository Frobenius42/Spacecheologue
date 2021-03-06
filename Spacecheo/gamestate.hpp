#pragma once
#include "state.hpp"
#include "world.hpp"

class GameState : public State
{
    public:
        GameState(StateStack& mystack, Context context);
        virtual ~GameState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
        void handlePlayerInput(sf::Keyboard::Key , bool);
    private:
        World mWorld;
        Player* mPlayer;
        sf::RectangleShape mPlayerShape;
};
