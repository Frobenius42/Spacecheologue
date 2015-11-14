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
    protected:
        Texture::ID id;
        b2Vec2 mPos;
};
