#include "world.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include "json.h"
#include "stonebloc.hpp"
#include "floorbloc.hpp"
#include "player.hpp"

World::World(TextureHolder* textures)
: mWorld(b2Vec2{0.f,10.f})
, mPlayerBody()
, mListeFixBody()
, mListeDynamicBody()
, mListeFixBloc()
, mListeDynamicBloc()
, mForceField(false)
, mJump(false)
, mJumpTime(0)
, mTextureHolder(textures)
, mBlocSize(0.4)
, mContactListener()
{
    Player mPlayer(&mWorld, 0.5, 4.5);
    mPlayerBody = mPlayer.getBody();

    mContactListener = new MyContactListener;
    mWorld.SetContactListener(mContactListener);

    mTextureHolder->load(Texture::Sol, "graphics/bloc2.png");
    mTextureHolder->load(Texture::Mur, "graphics/bloc1.png");
    mTextureHolder->load(Texture::Stone, "graphics/bloc3.png");

    createWorld("test.txt");
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
    std::cout << mContactListener->getNumFootContacts() << std::endl;
    mPlayerBody->SetAwake(true);
    for (unsigned int i=0; i<mListeDynamicBody.size(); ++i)
    {
        mListeDynamicBody[i]->SetAwake(true);
        if (mForceField)
        {
            b2Vec2 posA(mPlayerBody->GetPosition());
            b2Vec2 posB(mListeDynamicBody[i]->GetPosition());
            float dis(distance(posA, posB));
            if (dis<2.f)
            {
                b2Vec2 impulse(posB-posA);
                impulse.x = 10*impulse.x/dis;
                impulse.y = 10*impulse.y/dis;
                mListeDynamicBody[i]->ApplyLinearImpulse(impulse, mListeDynamicBody[i]->GetWorldCenter(), true);
            }
        }
        if (mDestructiveField)
        {
            b2Vec2 posA(mPlayerBody->GetPosition());
            b2Vec2 posB(mListeDynamicBody[i]->GetPosition());
            float dis(distance(posA, posB));
            if (dis<1.f)
            {
                mWorld.DestroyBody(mListeDynamicBody[i]);
                mListeDynamicBody.erase(mListeDynamicBody.begin()+i);
                mListeDynamicBloc.erase(mListeDynamicBloc.begin()+i);
            }
        }
    }
    if (mJump && mJumpTime==0 && mContactListener->getNumFootContacts()>=1)
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
    for (unsigned int i=0; i<mListeDynamicBloc.size(); ++i)
    {
        mListeDynamicBloc[i]->update();
    }
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
    return pow(pow((posA.x-posB.x),2)+pow((posA.y-posB.y),2),0.5f);
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
	blocBodyDef.position.Set(x+mBlocSize, y+mBlocSize);
	b2PolygonShape mBox;
	if (myid==Texture::Stone)
    {
        mBox.SetAsBox(mBlocSize-0.02, mBlocSize-0.02);
        b2FixtureDef mFixtureDef;
        mFixtureDef.shape = &mBox;
        blocBodyDef.type = b2_dynamicBody;
        blocBodyDef.fixedRotation = true;
        mFixtureDef.density = 100.0f;
        mFixtureDef.friction = 0.5f;
        mFixtureDef.restitution = 0.f;

        mBlocBody = mWorld.CreateBody(&blocBodyDef);
        mBlocBody->CreateFixture(&mFixtureDef);
        mListeDynamicBody.push_back(mBlocBody);
        StoneBloc* bloc = new StoneBloc(mBlocBody);
        mListeDynamicBloc.push_back(bloc);
    }
    else
    {
        mBox.SetAsBox(mBlocSize, mBlocSize);
        b2FixtureDef mFixtureDef;
        mFixtureDef.shape = &mBox;
        mBlocBody = mWorld.CreateBody(&blocBodyDef);
        mBlocBody->CreateFixture(&mBox, 0.0f);
        mListeFixBody.push_back(mBlocBody);
        FloorBloc* bloc = new FloorBloc(b2Vec2({x+mBlocSize,y+mBlocSize}));
        mListeFixBloc.push_back(bloc);
    }
}

void World::createWorld(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    if (!file)
    {
        std::cerr << "Error: can't open file " << fileName << std::endl;
        return;
    }

    Json::Value root;
    Json::Reader reader;
    if( !reader.parse(file, root, false) )
    {
        std::cout << "Error while reading level file:\n" << reader.getFormattedErrorMessages();
        return;
    }

    Json::Value tile = root["tile"];
    for (unsigned int i = 0 ; i < tile.size() ; i++)
    {
        unsigned int j(0);
        while( j < tile[i].size())
        {
            if (tile[i][j]=="P")
            {
                createBloc(Texture::Stone, j*2*mBlocSize, i*2*mBlocSize);
            }
            if (tile[i][j]=="S")
            {
                int depart(j);
                while (j<tile[i].size() && tile[i][j]=="S")
                {
                    FloorBloc* bloc = new FloorBloc(b2Vec2({j*2*mBlocSize+mBlocSize,i*2*mBlocSize+mBlocSize}));
                    mListeFixBloc.push_back(bloc);
                    j++;
                }
                b2Body* mBlocBody;
                b2BodyDef blocBodyDef;
                blocBodyDef.position.Set((depart+j)*2*mBlocSize/2, i*2*mBlocSize+mBlocSize);
                b2PolygonShape mBox;
                mBox.SetAsBox((j-depart)*mBlocSize, mBlocSize);
                b2FixtureDef mFixtureDef;
                mFixtureDef.shape = &mBox;
                mBlocBody = mWorld.CreateBody(&blocBodyDef);
                mBlocBody->CreateFixture(&mBox, 0.0f);
                mListeFixBody.push_back(mBlocBody);
                j--;
            }
            if (tile[i][j]=="M")
            {
                createBloc(Texture::Mur, j*2*mBlocSize, i*2*mBlocSize);
            }
        j++;
        }
    }
}

float World::getBlocSize()
{
    return mBlocSize;
}
