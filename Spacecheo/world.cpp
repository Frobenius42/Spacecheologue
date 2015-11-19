#include "world.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include "json.h"
#include "stonebloc.hpp"
#include "floorbloc.hpp"
#include "halfFloorBloc.hpp"
#include "player.hpp"

World::World(TextureHolder* textures, Player* player)
: mWorld()
, mPlayer(player)
, mListeFixBody()
, mListeDynamicBody()
, mListeFixBloc()
, mListeDynamicBloc()
, mForceField(false)
, mDestructiveField(false)
, mRight(false)
, mLeft(false)
, mBounce(false)
, mGravity(false)
, mJump(false)
, mJumpTime(0)
, mTextureHolder(textures)
, mBlocSize(0.4)
, mContactListener()
{
    mTextureHolder->load(Texture::Sol, "graphics/bloc2.png");
    mTextureHolder->load(Texture::Mur, "graphics/bloc1.png");
    mTextureHolder->load(Texture::Stone, "graphics/bloc3.png");
    mTextureHolder->load(Texture::HalfFloor, "graphics/halfbloc1.png");

    mWorld = new b2World(b2Vec2{0.f,10.f});
    mContactListener = new MyContactListener();
    mWorld->SetContactListener(mContactListener);
    createWorld("23.txt");
    *mPlayer = Player(mWorld, 0.5, 4.5, sf::Vector2f(2, 3));

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
    return mPlayer->getBody();
}

void World::updateWorld()
{
    std::cout << mContactListener->getNumFootContacts() << std::endl;
    b2Body* mPlayerBody = mPlayer->getBody();
    for (unsigned int i=0; i<mListeDynamicBloc.size(); ++i)
    {
        mListeDynamicBloc[i]->update();
    }
    for (unsigned int i=0; i<mListeFixBloc.size(); ++i)
    {
        mListeFixBloc[i]->update();
    }
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
                impulse.x = 20*impulse.x/dis;
                impulse.y = 20*impulse.y/dis;
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
                mWorld->DestroyBody(mListeDynamicBody[i]);
                mListeDynamicBody.erase(mListeDynamicBody.begin()+i);
                mListeDynamicBloc.erase(mListeDynamicBloc.begin()+i);
            }
        }
    }
    if (mBounce)
    {
        b2Fixture* fixtureListe(mPlayerBody->GetFixtureList());
        for(unsigned int i=0; i<4;++i)
        {
            fixtureListe[i].SetRestitution(1.);
        }
    }
    if (mRight)
    {
        mPlayerBody->SetAwake(true);
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = 2.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (mLeft)
    {
        mPlayerBody->SetAwake(true);
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = -2.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (!mLeft && !mRight)
    {
        b2Vec2 vel(mPlayerBody->GetLinearVelocity());
        vel.x = 0.;
        mPlayerBody->SetLinearVelocity(vel);
    }
    if (mJump && mJumpTime==0 && mContactListener->getNumFootContacts()>=1)
    {
        mPlayerBody->SetAwake(true);
        mPlayerBody->ApplyLinearImpulse( b2Vec2(0, -mPlayerBody->GetMass() * 5), mPlayerBody->GetWorldCenter(), true );
        mJumpTime=15;
    }
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    mWorld->Step(timeStep, velocityIterations, positionIterations);
    if (mJumpTime>0)
    {
        mPlayerBody->SetAwake(true);
        mJumpTime--;
    }
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
    mWorld->SetGravity(gravity);
}

void World::createBloc(Texture::ID myid, float x, float y)
{
	if (myid==Texture::Stone)
    {
        StoneBloc* bloc = new StoneBloc(mWorld, b2Vec2({x+mBlocSize,y+mBlocSize}), mBlocSize);
        mListeDynamicBloc.push_back(bloc);
        mListeDynamicBody.push_back(bloc->getBody());
    }
    else if (myid==Texture::HalfFloor)
    {
        HalfFloorBloc* bloc = new HalfFloorBloc(mWorld, b2Vec2({x+mBlocSize,y+mBlocSize}), mBlocSize, 0.);
        mListeFixBloc.push_back(bloc);
        mListeFixBody.push_back(bloc->getBody());
    }
    else
    {
        FloorBloc* bloc = new FloorBloc(b2Vec2({x+mBlocSize,y+mBlocSize}));
        mListeFixBody.push_back(bloc->getBody());
        mListeFixBloc.push_back(bloc);
    }
}

void World::createWorld(std::string fileName)
{
    //destruction du monde précédent
    mWorld->~b2World();
    /*for (unsigned int i=0; i<mListeDynamicBody.size(); ++i)
    {
        mWorld->DestroyBody(mListeDynamicBody[i]);
    }
    for (unsigned int i=0; i<mListeFixBody.size(); ++i)
    {
        mWorld->DestroyBody(mListeFixBody[i]);
    }*/
    mListeDynamicBloc.clear();
    mListeDynamicBody.clear();
    mListeFixBloc.clear();
    mListeFixBody.clear();
    mWorld = new b2World(b2Vec2{0.f,10.f});
    mWorld->SetContactListener(mContactListener);
    mContactListener->setNumFootContacts(0);

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
                mBlocBody = mWorld->CreateBody(&blocBodyDef);
                mBlocBody->CreateFixture(&mBox, 0.0f);
                mListeFixBody.push_back(mBlocBody);
                j--;
            }
            if (tile[i][j]=="M")
            {
                createBloc(Texture::Mur, j*2*mBlocSize, i*2*mBlocSize);
            }
            if (tile[i][j]=="H")
            {
                createBloc(Texture::HalfFloor, j*2*mBlocSize, i*2*mBlocSize);
            }
        j++;
        }
    }
}

float World::getBlocSize()
{
    return mBlocSize;
}

b2World* World::getWorld()
{
    return mWorld;
}

void World::setBounce(bool bo)
{
    mBounce = bo;
}

void World::setRight(bool bo)
{
    mRight = bo;
}

void World::setLeft(bool bo)
{
    mLeft = bo;
}
