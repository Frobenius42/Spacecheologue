#pragma once
#include "bloc.hpp"

class HalfFloorBloc: public Bloc
{
    public:
        HalfFloorBloc(b2World*, b2Vec2, float, float);
        void update();
};
