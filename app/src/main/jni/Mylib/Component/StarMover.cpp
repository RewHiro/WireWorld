//
// Created by vantan on 2016/02/17.
//

#include "StarMover.h"

#include "../GameObject.h"
#include "Transform.h"
#include "../Random.h"

StarMover::StarMover(rew::system::GameObject &game_object) :
Component(game_object,"StarMover"),
speed_(rew::system::Random::RandomRange(0.01f, 1.0f)),
count_(0)
{
    SetName(GetTypeName());
}

void StarMover::Update()
{
    GetGameObject().GetTransform()->Translate(Eigen::Vector3f(0,0,speed_));
    count_++;

    if(count_ > 60 * 10)
    {
        GetGameObjectTest()->Destory();
    }
}