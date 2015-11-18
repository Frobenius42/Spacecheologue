#pragma once

#include "player.hpp"
#include <Box2D/Box2D.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "bloc.hpp"
#include "textureholder.hpp"
#include <string>
#include "mycontactlistener.hpp"

class World
{
    public:
        World(TextureHolder*, Player*);
        std::vector<b2Body*> getListeFixBody();
        std::vector<b2Body*> getListeDynamicBody();
        std::vector<Bloc*> getListeFixBloc();
        std::vector<Bloc*> getListeDynamicBloc();
        b2Body* getPlayerBody();
        bool getForceField();
        void setGravity(b2Vec2);
        void setForceField(bool);
        void setDestructiveField(bool);
        void setJump(bool);
        void setLeft(bool);
        void setRight(bool);
        void setBounce(bool);
        bool getJump();
        void updateWorld();
        void createWorld(std::string);
        float getBlocSize();
        b2World* getWorld();
    private:
        float distance(b2Vec2, b2Vec2);
        void createBloc(Texture::ID, float, float);
    private:
        b2World* mWorld;
        Player* mPlayer;
        std::vector<b2Body*> mListeFixBody;
        std::vector<b2Body*> mListeDynamicBody;
        std::vector<Bloc*> mListeFixBloc;
        std::vector<Bloc*> mListeDynamicBloc;
        bool mForceField;
        bool mDestructiveField;
        bool mRight;
        bool mLeft;
        bool mBounce;
        bool mGravity;
        bool mJump;
        int mJumpTime;
        TextureHolder* mTextureHolder;
        float mBlocSize;
        MyContactListener* mContactListener;
};

