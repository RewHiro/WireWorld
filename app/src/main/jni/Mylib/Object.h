//
// Created by vantan on 2016/02/12.
//

#ifndef PRIMITIVEMONSTER03_OBJECT_H
#define PRIMITIVEMONSTER03_OBJECT_H

#include <string>

namespace rew {
    namespace system {
        class Object {
        public:
            explicit Object(const std::string& name = "Empty");
            virtual ~Object() = 0;

            inline const std::string& GetName() const { return name_; }

            inline bool IsDelete() const { return is_delete_; }
            virtual void Destory(){is_delete_ = true;}

            inline const Object& SetName(const std::string& name){name_ = name; return *this;}

        protected:
            std::string name_;
            unsigned int id_;
            bool is_delete_;

        private:
            static unsigned int GetInstanceID() {
                static unsigned int id = 0;
                return id++;
            }
        };
    }
}

#endif //PRIMITIVEMONSTER03_OBJECT_H
