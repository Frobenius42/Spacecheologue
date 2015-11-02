#include "world.hpp"

World::World()
: mWorld(b2Vec2{0.,10.})
, mPlayerBody()
, mListeBody()
, mGroundBody()
{

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
