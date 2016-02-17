//
// Created by vantan on 2016/02/14.
//

#include "Renderer.h"
#include "Mesh.h"

#include "RendererManager.h"
#include "GameObject.h"

#include <android/log.h>
#include "Eigen/Core"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            Renderer::Renderer
                    (
                    GameObject &game_object,
                    const std::vector<Material>& materials,
                    const std::shared_ptr<Mesh>& mesh
                    ) :
                    Component(game_object, "Renderer"),
                    mesh_(mesh)
            {
                for(const auto& material : materials)
                {
                    materials_.emplace(material.GetShaderType(), material);
                }
            }

            Renderer::Renderer
                    (
                            GameObject &game_object,
                            const Material& material,
                            const std::shared_ptr<Mesh>& mesh
                    ):
            Component(game_object, "Renderer"),
            mesh_(mesh)
            {
                materials_.emplace(material.GetShaderType(), material);
            }

            Renderer::~Renderer()
            {
                glDeleteBuffers(1, &vertex_buffer_);
                glDeleteBuffers(1, &index_buffer_);
                glDeleteVertexArrays(1, &vertex_array_buffer_);
            }

            void Renderer::Update()
            {
                if(!GetGameObject().IsDelete())return;
                Destory();
            }

            RendererManager& Renderer::GetRendererManager()
            {
                static RendererManager instance;
                return instance;
            }

            GLuint Renderer::CreateVertexArrayBuffer()
            {
                glGenVertexArrays(1, &vertex_array_buffer_);
                glBindVertexArray(vertex_array_buffer_);

                glGenBuffers(1, &vertex_buffer_);
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
                auto vertices =  mesh_->GetVertices();
                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

                __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", std::to_string(vertices.size()).c_str());

                glGenBuffers(1, &index_buffer_);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
                auto indices = mesh_->GetIndices();
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

                __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", std::to_string(indices.size()).c_str());

                glBindVertexArray(0);

                return vertex_array_buffer_;
            }
        }
    }
}