#include "statestack.hpp"
#include <functional>
#include <iostream>

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second();
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
            return;
    }
    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->Update(dt))
            return;
    }
}

void StateStack::draw()
{
    for (auto itr = mStack.rend(); itr != mStack.rbegin(); --itr)
    {
        (*itr)->Draw();
    }
}

void StateStack::applyPendingChanges()
{
    for (PendingChange change: mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;
            case Pop:
                mStack.pop_back();
                break;
            case Clear:
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

void StateStack::pushState(States::ID stateID)
{
    PendingChange change({Push, stateID});
    mPendingList.push_back(change);
}

void StateStack::popState()
{
    if (isEmpty())
        return;
    PendingChange change({Pop});
    mPendingList.push_back(change);
}

void StateStack::clearStates()
{
    PendingChange change({Clear});
    mPendingList.push_back(change);
}

bool StateStack::isEmpty() const
{
    return mStack.isEmpty();
}
