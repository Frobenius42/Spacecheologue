#pragma once
#include "bloc.hpp"

class StoneBloc: public Bloc
{
    public:
        StoneBloc(b2Body*);
        void update();
    private:
        b2Body* mBody;
};
