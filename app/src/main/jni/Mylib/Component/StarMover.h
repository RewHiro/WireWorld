//
// Created by vantan on 2016/02/17.
//

#ifndef PRIMITIVEMONSTER03_STARMOVER_H
#define PRIMITIVEMONSTER03_STARMOVER_H


#include "Component.h"

class StarMover : public rew::system::Component
{
public:
    StarMover(rew::system::GameObject& game_object);

    void Update();

private:
    float speed_;
    int count_;
};


#endif //PRIMITIVEMONSTER03_STARMOVER_H
