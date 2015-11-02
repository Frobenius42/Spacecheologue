#include "world.hpp"
#include <iostream>

World::World()
: mWorld(b2Vec2{0.,10.})
, mPlayerBody()
, mListeBody()
, mGroundBody()
, mTestBody()
{
    b2BodyDef groundBodyDef;  // def du sol
	groundBodyDef.position.Set(5.0f, 6.f);
	mGroundBody = mWorld.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(5.0f, 1.f);
	mGroundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef mBodyDef; // def du joueur
    mBodyDef.type = b2_dynamicBody; // le joueur est un corps dynamique
    mBodyDef.fixedRotation = true; // ULTRA IMPORTANT SINON LES COLLISIONS FONT ROTATER LE PLAYER !!!
	mBodyDef.position.Set(1.f, 1.f);

	b2PolygonShape mBox;
	mBox.SetAsBox(0.2f, 0.2f);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 0.0f;
	mFixtureDef.friction = 0.f;
	mFixtureDef.restitution = 0.f;

	mPlayerBody = mWorld.CreateBody(&mBodyDef);
    mPlayerBody->CreateFixture(&mFixtureDef);

    mFixtureDef.friction = 1.0f;
    mBodyDef.position.Set(4.f, 1.f);
    mTestBody = mWorld.CreateBody(&mBodyDef);
    b2MassData data;
    data.mass = 1000.;
    mTestBody->SetMassData(&data);
    mTestBody->CreateFixture(&mFixtureDef);
}

std::vector<b2Body*> World::getListeBody()
{
    return mListeBody;
}

b2Body* World::getPlayerBody()
{
    return mPlayerBody;
}

b2Body* World::getTestBody()
{
    return mTestBody;
}

void World::updateWorld()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    mWorld.Step(timeStep, velocityIterations, positionIterations);
}
