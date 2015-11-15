#include "gamestate.hpp"
#include <iostream>

GameState::GameState(StateStack& mystack, Context context)
: State(mystack, context)
, mWorld(context.textures)
, mPlayer(context.player)
, mPlayerShape()
{
    mPlayerShape.setSize({40,60});
    mPlayerShape.setFillColor(sf::Color::Green);
}


GameState::~GameState()
{

}

bool GameState::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        default:
            break;
    }
    return true;
}

void GameState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key==sf::Keyboard::Escape && isPressed)
    {
        requestStackPop();
    }
    if (key==sf::Keyboard::X)
    {
        if (isPressed)
            mWorld.setForceField(true);
        else
            mWorld.setForceField(false);
    }
    if (key==sf::Keyboard::C)
    {
        if (isPressed && !mWorld.getForceField())
            mWorld.setDestructiveField(true);
        else
            mWorld.setDestructiveField(false);
    }
    if (key==sf::Keyboard::V)
    {
        if (isPressed)
            mWorld.setGravity(b2Vec2{0., -10.});
        else
            mWorld.setGravity(b2Vec2{0., 10.});
    }
    if (key==sf::Keyboard::Space && isPressed)
    {
        mWorld.setJump(true);
    }
    if (key==sf::Keyboard::Right)
    {
        if (isPressed)
        {
            b2Vec2 vel(mWorld.getPlayerBody()->GetLinearVelocity());
            vel.x = 2.;
            mWorld.getPlayerBody()->SetLinearVelocity(vel);
        }
        else
        {
            b2Vec2 vel(mWorld.getPlayerBody()->GetLinearVelocity());
            vel.x = 0.;
            mWorld.getPlayerBody()->SetLinearVelocity(vel);
        }
    }
    if (key==sf::Keyboard::Left)
    {
        if (isPressed)
        {
            b2Vec2 vel(mWorld.getPlayerBody()->GetLinearVelocity());
            vel.x = -2.;
            mWorld.getPlayerBody()->SetLinearVelocity(vel);
        }
        else
        {
            b2Vec2 vel(mWorld.getPlayerBody()->GetLinearVelocity());
            vel.x = 0.;
            mWorld.getPlayerBody()->SetLinearVelocity(vel);
        }
    }
    if (key==sf::Keyboard::B)
    {
        if (isPressed)
        {
            (mWorld.getPlayerBody()->GetFixtureList())->SetRestitution(1.);
        }
        else
        {
            mWorld.getPlayerBody()->GetFixtureList()->SetRestitution(0.);
        }
    }
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
    float blocSize(mWorld.getBlocSize());
    mContext.window->clear();
    std::vector<Bloc*> liste(mWorld.getListeFixBloc());
    for (unsigned int i=0; i<liste.size(); ++i)
    {
        sf::Sprite sprite;
        sprite.setTexture(mContext.textures->get(liste[i]->getId()));
        b2Vec2 pos(liste[i]->getPos());
        sf::IntRect rect;
        rect.height = 200*blocSize;
        rect.width = 200*blocSize;
        sprite.setTextureRect(rect);
        float x = 100.*(pos.x-blocSize);
        float y = 100.*(pos.y-blocSize);
        sprite.setPosition(x ,y);
        mContext.window->draw(sprite);
    }
    liste = mWorld.getListeDynamicBloc();
    for (unsigned int i=0; i<liste.size(); ++i)
    {
        sf::Sprite sprite;
        sf::Texture texture(mContext.textures->get(liste[i]->getId()));
        sprite.setTexture(texture);
        sf::IntRect rect;
        rect.height = 200*blocSize;
        rect.width = 200*blocSize;
        sprite.setTextureRect(rect);
        b2Vec2 pos(liste[i]->getPos());
        float x = 100.*(pos.x-blocSize);
        float y = 100.*(pos.y-blocSize);
        sprite.setPosition(x ,y);
        mContext.window->draw(sprite);
    }
    mContext.window->draw(mPlayerShape);
    mContext.window->display();
}
