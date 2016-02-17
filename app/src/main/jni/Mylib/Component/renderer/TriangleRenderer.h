//
// Created by vantan on 2016/02/16.
//

#ifndef PRIMITIVEMONSTER03_TRIANGLERENDERER_H
#define PRIMITIVEMONSTER03_TRIANGLERENDERER_H

#include "Renderer.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            class TriangleRenderer : public Renderer
            {
            public:
                TriangleRenderer(GameObject &game_object, const Material& material, const std::shared_ptr<Mesh>& mesh);
                TriangleRenderer(GameObject &game_object, const std::vector<Material>& materials, const std::shared_ptr<Mesh>& mesh);

                static std::shared_ptr<TriangleRenderer>const Create(GameObject &game_object, const Material& material, const std::shared_ptr<Mesh>& mesh);
                static std::shared_ptr<TriangleRenderer>const Create(GameObject &game_object, const std::vector<Material>& materials, const std::shared_ptr<Mesh>& mesh);

                void Draw(const std::shared_ptr<Shader>& shader,const Eigen::Matrix4f& lp_matrix)override;

            private:
                GLuint CreateVertexArrayBuffer()override;
            };
        }
    }
}



#endif //PRIMITIVEMONSTER03_TRIANGLERENDERER_H
