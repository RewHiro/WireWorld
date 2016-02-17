//
// Created by vantan on 2016/02/14.
//

#ifndef PRIMITIVEMONSTER03_RENDERER_H
#define PRIMITIVEMONSTER03_RENDERER_H

#include "../Component.h"

#include <vector>
#include <map>
#include "../../Eigen/Core"

#include "Material.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            class Mesh;
            class RendererManager;
            class Shader;

            class Renderer : public Component
            {
            public:
                Renderer(GameObject &game_object, const Material& material, const std::shared_ptr<Mesh>& mesh);
                Renderer(GameObject &game_object, const std::vector<Material>& materials, const std::shared_ptr<Mesh>& mesh);

                ~Renderer();

                void Update();
                virtual void Draw(const std::shared_ptr<Shader>& shader,const Eigen::Matrix4f& lp_matrix) = 0;

                static RendererManager& GetRendererManager();

                const std::shared_ptr<Mesh>& GetMesh()const{return mesh_;}

            protected:

                virtual GLuint CreateVertexArrayBuffer() = 0;

                std::multimap<ShaderType , Material> materials_;
                std::shared_ptr<Mesh>const mesh_;
                GLuint vertex_buffer_;
                GLuint index_buffer_;
                GLuint vertex_array_buffer_;
            };
        }
    }
}




#endif //PRIMITIVEMONSTER03_RENDERER_H
