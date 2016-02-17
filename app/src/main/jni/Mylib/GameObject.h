//
// Created by vantan on 2016/02/12.
//

#ifndef PRIMITIVEMONSTER03_GAMEOBJECT_H
#define PRIMITIVEMONSTER03_GAMEOBJECT_H

#include "Object.h"
#include "GameObjectTask.h"

#include <memory>
#include <list>
#include <unordered_map>
#include <string>

namespace rew {
    namespace system {
        class Component;
        class Transform;
        class GameObjectTask;

        class GameObject : public Object {
        public:
            friend  class GameObjectTask;

            explicit GameObject(const std::string& name);
            ~GameObject();

            static std::shared_ptr<GameObject>const Create(const std::string& name);
            static std::shared_ptr<GameObject>const Find(const std::string& name);

            template<class T>
            std::shared_ptr<T> GetComponent()
            {
                const std::string name = typeid(T).name();
                return std::dynamic_pointer_cast<T>(component_map_.find(name)->second);
            }

            inline std::shared_ptr<Transform>const GetTransform()const
            {
                return transform_;
            }

            void AddComponent(const std::shared_ptr<Component>& component);

            static GameObjectTask& GetTask();

            void Destory();

        private:



            void Update();

            std::unordered_map<std::string, std::shared_ptr<Component>> component_map_;
            std::list<std::shared_ptr<Component>const> component_list_;
            std::shared_ptr<Transform>const transform_;
        };
    }
}


#endif //PRIMITIVEMONSTER03_GAMEOBJECT_H
