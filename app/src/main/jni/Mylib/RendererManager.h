//
// Created by vantan on 2016/02/14.
//

#ifndef PRIMITIVEMONSTER03_RENDERERMANAGER_H
#define PRIMITIVEMONSTER03_RENDERERMANAGER_H

#include "Object.h"

#include <list>
#include <memory>

namespace rew
{
    namespace system
    {
        class Camera;
        namespace renderer
        {
            class Renderer;

            class RendererManager : public Object
            {
            public:
                RendererManager();
                ~RendererManager();

                void Update(const Camera& camera);

                void Add(const std::shared_ptr<Renderer>& renderer);

            private:
                std::list<std::shared_ptr<Renderer>const> renderers_;
            };
        }
    }
}



#endif //PRIMITIVEMONSTER03_RENDERERMANAGER_H
