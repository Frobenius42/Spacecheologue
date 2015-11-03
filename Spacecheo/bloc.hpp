#pragma once
#include <SFML/Graphics.hpp>
#include "textureholder.hpp"

class Bloc
{
    public:
        enum type
        {
            Sol, Mur, Plateforme
        };
    public:
        Bloc(type, TextureHolder*, sf::Vector2f);
        sf::Vector2f getPos();
        void setPos(sf::Vector2f);
    private:
        sf::Texture* mTexture;
        sf::Vector2f mPos;
};
