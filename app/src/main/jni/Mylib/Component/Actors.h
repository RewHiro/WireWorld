//
// Created by vantan on 2016/02/16.
//

#ifndef PRIMITIVEMONSTER03_ACTORS_H
#define PRIMITIVEMONSTER03_ACTORS_H


#include "Component.h"

#include <random>
#include "../Eigen/Core"

class Actors : public rew::system::Component
{
public:
    Actors(rew::system::GameObject& game_object);

    void Update();

    static std::mt19937& GetRandom();

private:
    Eigen::Vector3f rotate_axis_;
    float translate_speed_;
    float rotate_speed_;
    float scale_speed_;
    int count_;

};


#endif //PRIMITIVEMONSTER03_ACTORS_H
