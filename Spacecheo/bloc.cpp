#include "bloc.hpp"
#include <iostream>

Bloc::Bloc(Texture::ID myid, b2Vec2 pos)
: id(myid)
, mPos(pos)
{

}

Texture::ID Bloc::getId()
{
    return id;
}

b2Vec2 Bloc::getPos()
{
    return mPos;
}

void Bloc::setPos(b2Vec2 pos)
{
    mPos = pos;
}
