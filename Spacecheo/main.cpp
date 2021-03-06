#include <SFML/Graphics.hpp>
#include "textureholder.hpp"
#include "font.hpp"
#include "player.hpp"
#include "state.hpp"
#include "application.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 650), "SpaceCheologue");
    window.setFramerateLimit(60);
    TextureHolder textures;
    FontHolder fonts;
    Player player;
    struct State::Context context(window, textures, fonts, player);
    Application app(context);
    int truc = app.run();

    return truc;
}
