#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "bloc.hpp"
#include "textureholder.hpp"

class World
{
    public:
        World(TextureHolder*);
        std::vector<b2Body*> getListeFixBody();
        std::vector<b2Body*> getListeDynamicBody();
        std::vector<Bloc*> getListeBloc();
        b2Body* getPlayerBody();
        bool getForceField();
        void setForceField(bool);
        void setJump(bool);
        bool getJump();
        void updateWorld();
    private:
        float distance(b2Vec2, b2Vec2);
        void createBloc(Bloc::type, float, float);
    private:
        b2World mWorld;
        b2Body* mPlayerBody;
        std::vector<b2Body*> mListeFixBody;
        std::vector<b2Body*> mListeDynamicBody;
        std::vector<Bloc*> mListeBloc;
        bool mForceField;
        bool mJump;
        int mJumpTime;
        TextureHolder* mTextureHolder;
};


