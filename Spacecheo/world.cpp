#include "world.hpp"
#include <iostream>

World::World()
: mWorld(b2Vec2{0.,10.})
, mPlayerBody()
, mListeBody()
, mGroundBody()
{
    b2BodyDef groundBodyDef;  // def du sol
	groundBodyDef.position.Set(5.0f, 4.f);
	mGroundBody = mWorld.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(5.0f, 1.f);
	mGroundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef mBodyDef; // def du joueur
    mBodyDef.type = b2_dynamicBody; // le joueur est un corps dynamique
    mBodyDef.fixedRotation = true; // ULTRA IMPORTANT SINON LES COLLISIONS FONT ROTATER LE PLAYER !!!
	mBodyDef.position.Set(1.f, 1.f);

	b2PolygonShape mBox;
	mBox.SetAsBox(1.f, 1.f);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 1.0f;
	mFixtureDef.friction = 0.0f;
	mFixtureDef.restitution = 0.f;

	mPlayerBody = mWorld.CreateBody(&mBodyDef);
    mPlayerBody->CreateFixture(&mFixtureDef);
}

std::vector<b2Body*> World::getListeBody()
{
    return mListeBody;
}

b2Body* World::getPlayerBody()
{
    return mPlayerBody;
}

void World::updateWorld()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    mWorld.Step(timeStep, velocityIterations, positionIterations);
}
