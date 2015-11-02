#include "gamestate.hpp"
#include <iostream>

GameState::GameState(StateStack& mystack, Context context)
: State(mystack, context)
, mWorld()
, mPlayer(context.player)
, mGroundShape()
, mPlayerShape()
{
    mGroundShape.setPosition(0., 300.);
    mGroundShape.setSize({1000,200});
    mGroundShape.setFillColor(sf::Color::Yellow);
    mPlayerShape.setSize({200,200});
    mPlayerShape.setFillColor(sf::Color::Green);
}

GameState::~GameState()
{

}

bool GameState::handleEvent(const sf::Event& event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        requestStackPop();
    }
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.updateWorld();
    b2Vec2 pos(mWorld.getPlayerBody()->GetPosition());
    sf::Vector2f siz(mPlayerShape.getSize());
    mPlayerShape.setPosition(100*pos.x-siz.x/2., 100*pos.y-siz.y/2.);
    return true;
}

void GameState::draw()
{
    mContext.window->clear();
    mContext.window->draw(mPlayerShape);
    mContext.window->draw(mGroundShape);
    mContext.window->display();
}
