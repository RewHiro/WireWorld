//
// Created by vantan on 2016/02/13.
//

#ifndef PRIMITIVEMONSTER03_GAMEOBJECTTASK_H
#define PRIMITIVEMONSTER03_GAMEOBJECTTASK_H

#include "Object.h"

#include <memory>
#include <list>
#include <unordered_map>
#include <string>

namespace rew
{
    namespace system
    {
    class GameObject;

        class GameObjectTask : public  Object
        {
        public:
            GameObjectTask();
            ~GameObjectTask();

            void Add(std::shared_ptr<GameObject>& game_object);
            std::shared_ptr<GameObject>const Find(const std::string& name);

            void Update();

            std::list<std::shared_ptr<GameObject>const>& GetList(){return game_object_list_;}

            private:
            std::list<std::shared_ptr<GameObject>const> game_object_list_;
            std::unordered_map<std::string, std::shared_ptr<GameObject>const>game_object_map_;
        };
    }
}


#endif //PRIMITIVEMONSTER03_GAMEOBJECTTASK_H
