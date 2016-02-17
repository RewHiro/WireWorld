//
// Created by vantan on 2016/02/12.
//

#include "Component.h"

#include <typeinfo>
#include <android/log.h>

namespace rew {
    namespace system {
        Component::Component(GameObject& game_object, const std::string& name) :
                Object(name),
                game_object_(game_object)
        {

        }

        //FIXME:nameを取得するとエラー、コンパイルする際のフラグが何か足りないかも
        std::string Component::GetTypeName()const
        {
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "GetTypeName");
            const std::type_info& id = typeid(*this);
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "ID");
            std::string name = id.name();
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", name.c_str());
            return name;
        }
    }
}