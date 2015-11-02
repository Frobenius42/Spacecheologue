#include "gamestate.hpp"
#include <iostream>

GameState::GameState(StateStack& mystack, Context context)
: State(mystack, context)
, mWorld()
, mPlayer(context.player)
, mGroundShape()
, mPlayerShape()
, mTestShape()
{
    mGroundShape.setPosition(0., 500.);
    mGroundShape.setSize({1000,200});
    mGroundShape.setFillColor(sf::Color::Yellow);
    mPlayerShape.setSize({40,40});
    mPlayerShape.setFillColor(sf::Color::Green);
    mTestShape.setSize({40,40});
    mTestShape.setFillColor(sf::Color::Red);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        b2Vec2 vel(mWorld.getPlayerBody()->GetLinearVelocity());
        vel.x = 1.;
        mWorld.getPlayerBody()->SetLinearVelocity(vel);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        b2Vec2 vel(mWorld.getPlayerBody()->GetLinearVelocity());
        vel.x = -1.;
        mWorld.getPlayerBody()->SetLinearVelocity(vel);
    }
    else
    {
        b2Vec2 vel(mWorld.getPlayerBody()->GetLinearVelocity());
        vel.x = 0.;
        mWorld.getPlayerBody()->SetLinearVelocity(vel);
    }
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.updateWorld();
    b2Vec2 pos(mWorld.getPlayerBody()->GetPosition());
    sf::Vector2f siz(mPlayerShape.getSize());
    mPlayerShape.setPosition(100*pos.x-siz.x/2., 100*pos.y-siz.y/2.);
    pos = mWorld.getTestBody()->GetPosition();
    siz = mTestShape.getSize();
    mTestShape.setPosition(100*pos.x-siz.x/2., 100*pos.y-siz.y/2.);
    return true;
}

void GameState::draw()
{
    mContext.window->clear();
    mContext.window->draw(mPlayerShape);
    mContext.window->draw(mTestShape);
    mContext.window->draw(mGroundShape);
    mContext.window->display();
}
