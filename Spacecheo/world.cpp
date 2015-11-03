#include "world.hpp"
#include <iostream>
#include <math.h>

World::World()
: mWorld(b2Vec2{0.,10.})
, mPlayerBody()
, mListeBody()
, mGroundBody()
, mTestBody()
, mForceField(false)
, mJump(false)
, mJumpTime(0)
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
    data.mass = 10.;
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
    if (mForceField)
    {
        b2Vec2 mPlayerPos(mPlayerBody->GetPosition());
        b2Vec2 mTestPos(mTestBody->GetPosition());
        float dis(distance(mPlayerPos, mTestPos));
        if (dis<2)
        {
            b2Vec2 impulse(mTestPos-mPlayerPos);
            impulse.x = impulse.x/dis;
            impulse.y = impulse.y/dis;
            mTestBody->ApplyLinearImpulse(impulse, mTestBody->GetPosition(), true);
        }
    }
    if (mJump && mJumpTime==0)
    {
        mPlayerBody->ApplyLinearImpulse( b2Vec2(0, -mPlayerBody->GetMass() * 5), mPlayerBody->GetWorldCenter(), true );
        mJumpTime=15;
    }
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    if (mJumpTime>0)
        mJumpTime--;
    mJump=false;
}

bool World::getForceField()
{
    return mForceField;
}

void World::setForceField(bool isActivated)
{
    mForceField = isActivated;
}

float World::distance(b2Vec2 posA, b2Vec2 posB)
{
    return pow(pow((posA.x-posB.x),2)+pow((posA.y-posB.y),2),0.5);
}

void World::setJump(bool jump)
{
    mJump = jump;
}

bool World::getJump()
{
    return mJump;
}
