#pragma once
#include "ressourceholder.hpp"
#include <SFML/Graphics.hpp>

namespace Texture
{
    enum ID {Sol, Mur, Stone, HalfFloor};
}

class TextureHolder: public ResourceHolder<sf::Texture, Texture::ID>
{
    public:
        TextureHolder();
};
