#pragma once
#include "bloc.hpp"

class FloorBloc: public Bloc
{
    public:
        FloorBloc(b2Vec2);
        void update();
};
