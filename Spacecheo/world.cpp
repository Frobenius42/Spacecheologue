#include "world.hpp"
#include <iostream>
#include <math.h>

World::World(TextureHolder* textures)
: mWorld(b2Vec2{0.,10.})
, mPlayerBody()
, mListeFixBody()
, mListeDynamicBody()
, mListeFixBloc()
, mListeDynamicBloc()
, mForceField(false)
, mJump(false)
, mJumpTime(0)
, mTextureHolder(textures)
{

    b2BodyDef mBodyDef; // def du joueur
    mBodyDef.type = b2_dynamicBody; // le joueur est un corps dynamique
    mBodyDef.fixedRotation = true; // ULTRA IMPORTANT SINON LES COLLISIONS FONT ROTATER LE PLAYER !!!
	mBodyDef.position.Set(2.5f, 3.5f);

	b2PolygonShape mBox;
	mBox.SetAsBox(0.2f, 0.2f);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 0.0f;
	mFixtureDef.friction = 0.f;
	mFixtureDef.restitution = 0.f;

	mPlayerBody = mWorld.CreateBody(&mBodyDef);
    mPlayerBody->CreateFixture(&mFixtureDef);

    mTextureHolder->load(Texture::Sol, "graphics/bloc2.png");
    mTextureHolder->load(Texture::Mur, "graphics/bloc1.png");
    mTextureHolder->load(Texture::Plateforme, "graphics/bloc3.png");

    createBloc(Texture::Sol, 0., 4.);
    createBloc(Texture::Sol, 1., 4.);
    createBloc(Texture::Sol, 2., 4.);
    createBloc(Texture::Sol, 3., 4.);
    createBloc(Texture::Sol, 4., 4.);
    createBloc(Texture::Plateforme, 3., 3.);
    createBloc(Texture::Plateforme, 3., 2.);
    createBloc(Texture::Plateforme, 1., 3.);
    createBloc(Texture::Plateforme, 1., 2.);
}

std::vector<b2Body*> World::getListeFixBody()
{
    return mListeFixBody;
}

std::vector<b2Body*> World::getListeDynamicBody()
{
    return mListeDynamicBody;
}

std::vector<Bloc*> World::getListeFixBloc()
{
    return mListeFixBloc;
}

std::vector<Bloc*> World::getListeDynamicBloc()
{
    return mListeDynamicBloc;
}

b2Body* World::getPlayerBody()
{
    return mPlayerBody;
}

void World::updateWorld()
{
    if (mForceField)
    {
        for (unsigned int i=0; i<mListeDynamicBody.size(); ++i)
        {
            b2Vec2 posA(mPlayerBody->GetPosition());
            b2Vec2 posB(mListeDynamicBody[i]->GetPosition());
            float dis(distance(posA, posB));
            if (dis<2.)
            {
                b2Vec2 impulse(posB-posA);
                impulse.x = 10*impulse.x/dis;
                impulse.y = 10*impulse.y/dis;
                mListeDynamicBody[i]->ApplyLinearImpulse(impulse, mListeDynamicBody[i]->GetWorldCenter(), true);
            }
        }
    }
    if (mDestructiveField)
    {
        for (unsigned int i=0; i<mListeDynamicBody.size(); ++i)
        {
            b2Vec2 posA(mPlayerBody->GetPosition());
            b2Vec2 posB(mListeDynamicBody[i]->GetPosition());
            float dis(distance(posA, posB));
            if (dis<1.)
            {
                mWorld.DestroyBody(mListeDynamicBody[i]);
                mListeDynamicBody.erase(mListeDynamicBody.begin()+i);
                mListeDynamicBloc.erase(mListeDynamicBloc.begin()+i);
            }
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

void World::setDestructiveField(bool isActivated)
{
    mDestructiveField = isActivated;
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

void World::setGravity(b2Vec2 gravity)
{
    mWorld.SetGravity(gravity);
}

void World::createBloc(Texture::ID myid, float x, float y)
{
    b2Body* mBlocBody;
    b2BodyDef blocBodyDef;
	blocBodyDef.position.Set(x, y);
	b2PolygonShape mBox;
    mBox.SetAsBox(0.5f, 0.5f);
    b2FixtureDef mFixtureDef;
    mFixtureDef.shape = &mBox;
	if (myid==Texture::Plateforme)
    {
        blocBodyDef.type = b2_dynamicBody;
        blocBodyDef.fixedRotation = true;
        mFixtureDef.density = 1.0f;
        mFixtureDef.friction = 0.5f;
        mFixtureDef.restitution = 0.f;

        b2MassData mass;
        mass.mass = 100.;
        mBlocBody = mWorld.CreateBody(&blocBodyDef);
        mBlocBody->CreateFixture(&mFixtureDef);
        mBlocBody->SetMassData(&mass);
        mListeDynamicBody.push_back(mBlocBody);
        Bloc* bloc = new Bloc(myid, mBlocBody);
        mListeDynamicBloc.push_back(bloc);
    }
    else
    {
        mBlocBody = mWorld.CreateBody(&blocBodyDef);
        mBlocBody->CreateFixture(&mBox, 0.0f);
        mListeFixBody.push_back(mBlocBody);
        Bloc* bloc = new Bloc(myid, mBlocBody);
        mListeFixBloc.push_back(bloc);
    }
}
