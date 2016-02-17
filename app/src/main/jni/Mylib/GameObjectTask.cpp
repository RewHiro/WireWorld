//
// Created by vantan on 2016/02/13.
//

#include "GameObjectTask.h"

#include "GameObject.h"

namespace rew
{
    namespace system
    {
        GameObjectTask::GameObjectTask():
        Object()
        {

        }

        GameObjectTask::~GameObjectTask()
        {
            game_object_list_.clear();
            game_object_map_.clear();
        }

        void GameObjectTask::Add(std::shared_ptr<GameObject>& game_object)
        {
            game_object_list_.emplace_back(game_object);
            game_object_map_.emplace(game_object->GetName(), game_object);
        }

        std::shared_ptr<GameObject>const GameObjectTask::Find(const std::string& name)
        {
            return game_object_map_.find(name)->second;
        }

        void GameObjectTask::Update()
        {
            for(const auto& game_object : game_object_list_)
            {
                game_object->Update();
            }

            auto itr = game_object_map_.cbegin();
            while(itr != game_object_map_.cend())
            {
                if(itr->second->IsDelete())
                {
                    itr = game_object_map_.erase(itr);
                }
                else
                {
                    ++itr;
                }
            }

            game_object_list_.remove_if([](const std::shared_ptr<GameObject>& game_object){return game_object->IsDelete();});

        }
    }
}