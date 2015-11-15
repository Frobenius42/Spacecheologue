#pragma once
#include <SFML/Graphics.hpp>
#include "textureholder.hpp"
#include <Box2D/Box2D.h>

class Bloc
{
    public:
        Bloc(Texture::ID, b2Vec2);
        Texture::ID getId();
        b2Vec2 getPos();
        b2Body* getBody();
        void setPos(b2Vec2);
        virtual void update() = 0;
    protected:
        Texture::ID id;
        b2Vec2 mPos;
        b2Body* mBody;
};
