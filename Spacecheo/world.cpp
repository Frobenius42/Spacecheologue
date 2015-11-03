#include "world.hpp"
#include <iostream>
#include <math.h>

World::World(TextureHolder* textures)
: mWorld(b2Vec2{0.,10.})
, mPlayerBody()
, mListeFixBody()
, mListeDynamicBody()
, mListeBloc()
, mForceField(false)
, mJump(false)
, mJumpTime(0)
, mTextureHolder(textures)
{

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
}

std::vector<b2Body*> World::getListeFixBody()
{
    return mListeFixBody;
}

std::vector<b2Body*> World::getListeDynamicBody()
{
    return mListeDynamicBody;
}

std::vector<Bloc*> World::getListeBloc()
{
    return mListeBloc;
}

b2Body* World::getPlayerBody()
{
    return mPlayerBody;
}

void World::updateWorld()
{
    if (mForceField)
    {

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

void World::createBloc(Bloc::type id, float x, float y)
{
    b2BodyDef blocBodyDef;
	blocBodyDef.position.Set(x, y);
   	b2Body* mBlocBody = mWorld.CreateBody(&blocBodyDef);
	b2PolygonShape blocBox;
	blocBox.SetAsBox(0.5f, 0.5f);
	mBlocBody->CreateFixture(&blocBox, 0.0f);
	mListeFixBody.push_back(mBlocBody);
	Bloc bloc(id, mTextureHolder, sf::Vector2f{x,y});
	mListeBloc.push_back(&bloc);
}
