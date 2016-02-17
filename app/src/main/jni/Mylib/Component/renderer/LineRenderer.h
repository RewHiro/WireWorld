//
// Created by vantan on 2016/02/16.
//

#ifndef PRIMITIVEMONSTER03_LINERENDERER_H
#define PRIMITIVEMONSTER03_LINERENDERER_H

#include "Renderer.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            class LineRenderer : public Renderer
            {
            public:
                LineRenderer(GameObject &game_object, const Material& material, const std::shared_ptr<Mesh>& mesh);
                LineRenderer(GameObject &game_object, const std::vector<Material>& materials, const std::shared_ptr<Mesh>& mesh);

                static std::shared_ptr<LineRenderer>const Create(GameObject &game_object, const Material& material, const std::shared_ptr<Mesh>& mesh);
                static std::shared_ptr<LineRenderer>const Create(GameObject &game_object, const std::vector<Material>& materials, const std::shared_ptr<Mesh>& mesh);

                void Draw(const std::shared_ptr<Shader>& shader,const Eigen::Matrix4f& lp_matrix)override;

            private:
                GLuint CreateVertexArrayBuffer()override;
            };
        }
    }
}



#endif //PRIMITIVEMONSTER03_LINERENDERER_H
