//
// Created by vantan on 2016/02/12.
//

#include "Transform.h"
#include "GameObject.h"

#include <android/log.h>

namespace rew {
    namespace system {
        Transform::Transform
                (
                        GameObject& game_object,
                        const Eigen::Vector3f& pos,
                        const Eigen::Vector3f& scale,
                        const Eigen::Quaternionf rotate
                ) :
                Component(game_object, ""),
                position_(pos),
                scale_(scale),
                rotate_(rotate),
                parent_(nullptr)
        {
            SetName(GetTypeName());
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "CREATE TRANSFORM");
        }

        void Transform::Update()
        {
            if(!GetGameObject().IsDelete())return;
            for(auto child : children_)
            {
                child->Destory();
            }
        }
    }
}