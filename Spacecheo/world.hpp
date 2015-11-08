#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "bloc.hpp"
#include "textureholder.hpp"
#include <string>

class World
{
    public:
        World(TextureHolder*);
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
        bool getJump();
        void updateWorld();
        void createWorld(std::string, sf::Vector2f);
    private:
        float distance(b2Vec2, b2Vec2);
        void createBloc(Texture::ID, float, float);
    private:
        b2World mWorld;
        b2Body* mPlayerBody;
        std::vector<b2Body*> mListeFixBody;
        std::vector<b2Body*> mListeDynamicBody;
        std::vector<Bloc*> mListeFixBloc;
        std::vector<Bloc*> mListeDynamicBloc;
        bool mForceField;
        bool mDestructiveField;
        bool mJump;
        int mJumpTime;
        TextureHolder* mTextureHolder;
};


