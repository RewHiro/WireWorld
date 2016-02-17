//
// Created by vantan on 2016/02/12.
//

#ifndef PRIMITIVEMONSTER03_COMPONENT_H
#define PRIMITIVEMONSTER03_COMPONENT_H

#include "../Object.h"

namespace rew {
    namespace system {
        class GameObject;

        class Component : public Object {
        public:
            explicit Component(GameObject& game_object, const std::string& name);

            virtual std::string GetTypeName()const;

            virtual void Start(){}
            virtual void Update(){}

            inline const GameObject& GetGameObject()const{return game_object_;}
            inline GameObject* const GetGameObjectTest()const{return &game_object_;}

        private:
            GameObject& game_object_;
        };
    }
}

#endif //PRIMITIVEMONSTER03_COMPONENT_H
