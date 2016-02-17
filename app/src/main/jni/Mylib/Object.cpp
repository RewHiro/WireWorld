//
// Created by vantan on 2016/02/12.
//

#include "Object.h"
#include <android/log.h>

namespace rew {
    namespace system {

        Object::Object(const std::string& name):
        name_(name),
        id_(GetInstanceID()),
        is_delete_(false)
        {
//            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", name.c_str());
        }

        Object::~Object()
        {

        }
    }
}
