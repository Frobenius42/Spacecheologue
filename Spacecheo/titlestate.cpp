#include "titlestate.hpp"

TitleState::TitleState(StateStack& mystack, Context context)
: State(mystack, context)
, mBackgroundSprite()
, mText()
, mShowText(true)
, mTextEffectTime()
{

}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return true;
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    if (mTextEffectTime >= sf::seconds(0.8f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    return true;
}

void TitleState::draw()
{
    mContext.window->draw(mBackgroundSprite);
    if (mShowText)
        mContext.window->draw(mText);
}
