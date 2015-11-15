#pragma once
#include "bloc.hpp"

class StoneBloc: public Bloc
{
    public:
        StoneBloc(b2World*, b2Vec2, float);
        void update();
};
