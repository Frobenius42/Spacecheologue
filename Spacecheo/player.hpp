#pragma once
#include <Box2D/Box2D.h>
#include <SFML/System.hpp>

class Player
{
    public:
        Player(b2World*,float ,float);
        Player();
        b2Body* getBody();
        sf::Vector2f getPos();
    private:
        sf::Vector2f mPos;
        b2Body* mBody;
};
