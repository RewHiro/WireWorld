//
// Created by vantan on 2016/02/12.
//

#include "GameObject.h"

#include "Component/Transform.h"
#include "GameObjectTask.h"

#include <android/log.h>

namespace rew {
    namespace system {
        GameObject::GameObject(const std::string& name) :
        Object(name),
        transform_(std::make_shared<Transform>(*this))
        {
            __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "TEST");
            AddComponent(transform_);
        }

        GameObject::~GameObject()
        {
            component_map_.clear();
            component_list_.clear();
        }

        std::shared_ptr<GameObject>const GameObject::Create(const std::string& name)
        {
            auto game_object = std::make_shared<GameObject>(name);

            auto& task = GetTask();

            task.Add(game_object);

            return game_object;
        }

        std::shared_ptr<GameObject>const GameObject::Find(const std::string& name)
        {
            auto task = GetTask();
            return task.Find(name);
        }

        void GameObject::AddComponent(const std::shared_ptr<Component>& component)
        {
            component_list_.emplace_front(component);
            component_map_.emplace(component->GetTypeName(), component);
        }

        GameObjectTask& GameObject::GetTask()
        {
            static GameObjectTask instance;
            return instance;
        }

        void GameObject::Destory()
        {
            Object::Destory();
            for(auto& component : component_list_)
            {
                component->Destory();
            }
        }

        void GameObject::Update()
        {
            for(const auto& component : component_list_)
            {
                component->Update();
            }

            //TODO:消す処理

            auto itr = component_map_.cbegin();
            while(itr != component_map_.cend())
            {
                if(itr->second->IsDelete())
                {
                    itr = component_map_.erase(itr);
                }
                else
                {
                    ++itr;
                }
            }
            component_list_.remove_if([](const std::shared_ptr<Component>& component){return component->IsDelete();});
        }
    }
}
