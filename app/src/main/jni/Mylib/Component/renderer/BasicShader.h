//
// Created by vantan on 2016/02/11.
//

#ifndef PRIMITIVEMONSTER03_BASICSHADER_H
#define PRIMITIVEMONSTER03_BASICSHADER_H

#include "Shader.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            class BasicShader : public Shader
            {
            public:
                BasicShader();

                void Bind()const override ;
                void UnBind()const override ;
                void Upload(const float* wlp_matrix, const Material& material)const override ;

            private:
                GLuint unif_wlp_matrix;
                GLuint unif_color;
            };
        }
    }
}



#endif //PRIMITIVEMONSTER03_BASICSHADER_H
