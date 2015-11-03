#pragma once
#include <SFML/Graphics.hpp>

namespace Blocs
{
    enum ID {Sol, Mur, Plateforme};
}

class Bloc
{
    public:
        Bloc(Blocs::ID);
    private:
        sf::Texture* mTexture;
};
