#pragma once
#include <SFML/Graphics.hpp>
#include "textureholder.hpp"
#include <Box2D/Box2D.h>

class Bloc
{
    public:
        Bloc(Texture::ID, b2Body*);
        Texture::ID getId();
        b2Body* getBody();
    protected:
        Texture::ID id;
        b2Body* mBody;
};
