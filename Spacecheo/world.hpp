#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include <SFML/Graphics.hpp>

class World
{
    public:
        World();
        std::vector<b2Body*> getListeBody();
        b2Body* getPlayerBody();
        b2Body* getTestBody();
        void updateWorld();
    private:
        b2World mWorld;
        b2Body* mPlayerBody;
        std::vector<b2Body*> mListeBody;
        b2Body* mGroundBody;
        b2Body* mTestBody;
};


