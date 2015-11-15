#include "stonebloc.hpp"

StoneBloc::StoneBloc(b2World* world, b2Vec2 pos, float mBlocSize)
: Bloc(Texture::Stone, pos)
{
    b2BodyDef blocBodyDef;
    blocBodyDef.position.Set(pos.x, pos.y);
    b2PolygonShape mBox;
    mBox.SetAsBox(mBlocSize-0.02, mBlocSize-0.02);
    b2FixtureDef mFixtureDef;
    mFixtureDef.shape = &mBox;
    blocBodyDef.type = b2_dynamicBody;
    blocBodyDef.fixedRotation = true;
    mFixtureDef.density = 100.0f;
    mFixtureDef.friction = 0.5f;
    mFixtureDef.restitution = 0.f;
    mBody = world->CreateBody(&blocBodyDef);
    mBody->CreateFixture(&mFixtureDef);
}

void StoneBloc::update()
{
    mPos = mBody->GetPosition();
}
