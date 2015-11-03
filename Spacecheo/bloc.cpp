#include "bloc.hpp"

Bloc::Bloc(type id, TextureHolder* textures, sf::Vector2f pos)
: mTexture()
, mPos(pos)
{
    switch (id)
    {
        case Sol:
            mTexture = &textures->get(Texture::Sol);
            break;
        case Mur:
            mTexture = &textures->get(Texture::Mur);
            break;
        case Plateforme:
            mTexture = &textures->get(Texture::Plateforme);
            break;
    }
}

sf::Vector2f Bloc::getPos()
{
    return mPos;
}

void Bloc::setPos(sf::Vector2f newPos)
{
    mPos = newPos;
}
