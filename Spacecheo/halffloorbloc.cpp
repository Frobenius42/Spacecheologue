#include "halfFloorbloc.hpp"
#include <iostream>

HalfFloorBloc::HalfFloorBloc(b2World* world, b2Vec2 pos,float mBlocSize, float rotation)
: Bloc(Texture::HalfFloor, pos)
, mTimer(0)
{
    b2BodyDef blocBodyDef;
    blocBodyDef.position.Set(pos.x, pos.y);
    b2PolygonShape mBox;
    b2Vec2* vertices = new b2Vec2[3];
    vertices[0].Set(mBlocSize, -mBlocSize);
    vertices[1].Set(mBlocSize, mBlocSize);
    vertices[2].Set(-mBlocSize, mBlocSize);
    mBox.Set(vertices, 3);
    b2FixtureDef mFixtureDef;
    mFixtureDef.shape = &mBox;
    mBody = world->CreateBody(&blocBodyDef);
    mBody->CreateFixture(&mFixtureDef);
}

void HalfFloorBloc::update()
{
    b2ContactEdge* contactList(mBody->GetContactList());
    for (b2ContactEdge* ce = contactList; ce; ce = ce->next)
    {
        if (ce->contact->IsTouching() && mTimer>15)
        {
            b2Body* bodyA(ce->other);
            bodyA->SetAwake(false);
            mTimer = 0;
        }
    }
    mTimer++;
}
