#pragma once
#include "ressourceholder.hpp"

namespace Texture
{
    enum ID {};
}

class TextureHolder: public ResourceHolder<sf::Texture, Texture::ID>
{
    TextureHolder();
};
