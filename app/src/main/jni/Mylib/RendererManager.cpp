//
// Created by vantan on 2016/02/14.
//


#include "RendererManager.h"

#include <android/log.h>

#include "Component/renderer/Renderer.h"
#include "Component/renderer/BasicShader.h"
#include "GameObject.h"
#include "Component/Camera.h"
#include "camera/CameraMatrix.h"


namespace rew
{
    namespace system
    {
        namespace renderer
        {
            RendererManager::RendererManager() :
                    Object()
            {

            }

            RendererManager::~RendererManager()
            {
                renderers_.clear();
            }

            void RendererManager::Update(const Camera& camera)
            {

                renderers_.remove_if([](const std::shared_ptr<Renderer>& renderer){return renderer->IsDelete();});

                std::shared_ptr<Shader> shader = std::make_shared<BasicShader>();

                shader->Bind();

                Eigen::Matrix4f lp_matrix = camera.Perspective() * camera.LookAt();

                for(auto& renderer : renderers_)
                {
                    renderer->Draw(shader, lp_matrix);
                }
            }


            void RendererManager::Add(const std::shared_ptr<Renderer>& renderer)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "ADD RENDERER");
                renderers_.emplace_back(renderer);
            }
        }
    }
}