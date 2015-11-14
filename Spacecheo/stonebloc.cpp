#include "stonebloc.hpp"

StoneBloc::StoneBloc(b2Body* body)
: Bloc(Texture::Stone, body->GetPosition())
, mBody(body)
{

}

void StoneBloc::update()
{
    mPos = mBody->GetPosition();
}
