#include "gamestate.hpp"
#include <iostream>

GameState::GameState(StateStack& mystack, Context context)
: State(mystack, context)
, mWorld(context.textures)
, mPlayer(context.player)
, mPlayerShape()
, m_jumpTimeout(0)
{
    mPlayerShape.setSize({40,40});
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        mWorld.setForceField(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        mWorld.setForceField(false);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (m_jumpTimeout == 0)
        {
            mWorld.setJump(!mWorld.getJump());
            m_jumpTimeout = 15;
        }
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
    if (m_jumpTimeout>0)
        m_jumpTimeout--;
    return true;
}

void GameState::draw()
{
    mContext.window->clear();
    mContext.window->draw(mPlayerShape);
    mContext.window->display();
}
