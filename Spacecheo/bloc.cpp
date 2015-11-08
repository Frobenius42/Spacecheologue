#include "bloc.hpp"
#include <iostream>

Bloc::Bloc(Texture::ID myid, b2Body* body)
: id(myid)
, mBody(body)
{

}

Texture::ID Bloc::getId()
{
    return id;
}

b2Body* Bloc::getBody()
{
    return mBody;
}

