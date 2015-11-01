#include "application.hpp"
#include "titlestate.hpp"
#include "gamestate.hpp"

Application::Application(State::Context context)
: mStateStack(context)
, mWindow(context.window)
{
    mStateStack.pushState(States::Title);
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SpeechState>(States::Speech);
}

void Application::processInput()
{
    while(mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mStateStack.draw());
}

int Application::run()
{
    while(!mStateStack.isEmpty())
    {
        processInput();
        update();
        render();
    }
    mWindow.close();
    return 0;
}
