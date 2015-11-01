#include "gamestate.hpp"

GameState::GameState(StateStack& mystack, Context context)
: mWorld()
, mPlayer(context.player)
{

}

bool GameState::handleEvent(const sf::Event& event)
{
    return true;
}

bool GameState::update(sf::Time dt)
{
    return true;
}

void GameState::draw()
{

}
