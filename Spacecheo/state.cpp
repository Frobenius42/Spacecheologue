#include "state.hpp"

State::State(StateStack& mystack, Context context)
: mStack(&mystack)
, mContext(context)
{

}

void requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);
}

void requestStackPop()
{
    mStack->popState();
}

void requestStateClear()
{
    mStack->clearStates();
}

Context getContext() const
{
    return mContext;
}
