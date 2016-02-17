//
// Created by vantan on 2016/02/16.
//

#include "Actors.h"
#include "../GameObject.h"
#include "Transform.h"

Actors::Actors(rew::system::GameObject& game_object):
Component(game_object, "Actors"),
rotate_axis_(Eigen::Vector3f::Zero()),
translate_speed_(0.0f),
rotate_speed_(0.0f),
scale_speed_(0.0f),
count_(0)
{
    SetName(GetTypeName());

    std::uniform_real_distribution<float>rand(-0.05f, 0.05f);
    translate_speed_ = rand(GetRandom());
    rotate_speed_ = rand(GetRandom());
    scale_speed_ = rand(GetRandom());
    rotate_axis_ = Eigen::Vector3f(rand(GetRandom()), rand(GetRandom()), rand(GetRandom()));
    rotate_axis_.normalize();

    std::uniform_real_distribution<float>rand_scale(0.5f, 1.0f);
    float scale = rand_scale(GetRandom());
    GetGameObject().GetTransform()->SetScale(Eigen::Vector3f::Ones() * scale);
}

void Actors::Update()
{
    GetGameObject().GetTransform()->Rotation(Eigen::Quaternionf(Eigen::AngleAxisf(rotate_speed_, rotate_axis_)));
    count_++;

    if(!(count_ >= 60 * 20))return;
    GetGameObjectTest()->Destory();
}

std::mt19937& Actors::GetRandom()
{
    static std::random_device seed;
    static std::mt19937 random(seed());
    return random;
}