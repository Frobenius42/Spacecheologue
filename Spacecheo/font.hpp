#pragma once
#include "ressourceholder.hpp"

namespace Font
{
    enum ID {};
}

class FontHolder: public ResourceHolder<sf::Font, Font::ID>
{
    FontHolder();
};
