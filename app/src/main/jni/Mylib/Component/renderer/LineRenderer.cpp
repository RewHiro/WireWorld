//
// Created by vantan on 2016/02/16.
//

#include "LineRenderer.h"

#include "Mesh.h"
#include "RendererManager.h"
#include "../../GameObject.h"
#include "../Transform.h"


namespace rew
{
    namespace system
    {
        namespace renderer
        {
            LineRenderer::LineRenderer
                    (
                            GameObject &game_object,
                            const std::vector<Material>& materials,
                            const std::shared_ptr<Mesh>& mesh
                    ) :
                    Renderer(game_object, materials, mesh)
            {
                SetName(GetTypeName());
                CreateVertexArrayBuffer();
            }

            LineRenderer::LineRenderer
                    (
                            GameObject &game_object,
                            const Material& material,
                            const std::shared_ptr<Mesh>& mesh
                    ):
                    Renderer(game_object, material, mesh)
            {
                SetName(GetTypeName());
                CreateVertexArrayBuffer();
            }

            std::shared_ptr<LineRenderer>const LineRenderer::Create
                    (
                            GameObject &game_object,
                            const Material& material,
                            const std::shared_ptr<Mesh>& mesh
                    )
            {

                std::shared_ptr<LineRenderer>const renderer = std::make_shared<LineRenderer>(game_object, material, mesh);

                auto& renderer_manager = GetRendererManager();

                renderer_manager.Add(renderer);

                return renderer;
            }

            std::shared_ptr<LineRenderer>const LineRenderer::Create
                    (
                            GameObject &game_object,
                            const std::vector<Material>& materials,
                            const std::shared_ptr<Mesh>& mesh
                    )
            {

                std::shared_ptr<LineRenderer>const renderer = std::make_shared<LineRenderer>(game_object, materials, mesh);

                auto& renderer_manager = GetRendererManager();

                renderer_manager.Add(renderer);

                return renderer;
            }

            void LineRenderer::Draw(const std::shared_ptr<Shader>& shader,const Eigen::Matrix4f& lp_matrix)
            {
                auto range = materials_.equal_range(shader->GetType());

                auto itr = range.first;
                if(itr == range.second)return;

                glBindVertexArray(vertex_array_buffer_);

                glLineWidth(15.0f);

                Eigen::Matrix4f wlp_matrix = lp_matrix * GetGameObject().GetTransform()->GetWorldMatrix();

                for(itr = range.first; itr != range.second; itr++)
                {
                    shader->Upload(wlp_matrix.data(), itr->second);
                    glDrawElements(GL_LINES, mesh_->GetWireIndices().size(), GL_UNSIGNED_INT, 0);
                }
                glBindVertexArray(0);
            }

            GLuint LineRenderer::CreateVertexArrayBuffer()
            {
                glGenVertexArrays(1, &vertex_array_buffer_);
                glBindVertexArray(vertex_array_buffer_);

                glGenBuffers(1, &vertex_buffer_);
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
                auto vertices =  mesh_->GetVertices();
                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

                glGenBuffers(1, &index_buffer_);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
                auto indices = mesh_->GetWireIndices();
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

                glBindVertexArray(0);

                return vertex_array_buffer_;
            }
        }
    }
}