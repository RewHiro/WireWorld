//
// Created by vantan on 2016/02/11.
//

#ifndef PRIMITIVEMONSTER03_SHADER_H
#define PRIMITIVEMONSTER03_SHADER_H

#include <GLES3/gl31.h>

#include "../../Object.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            class Material;

            class Shader : public Object
            {
            public:

                enum class Type
                {
                    BASIC,
                    NONE,
                };

                Shader
                        (
                                const char* vertex_source,
                                const char* fragment_source,
                                Type type = Type::BASIC
                        );
                virtual ~Shader() = 0;

                static GLint LoadShader
                        (
                                const char* source,
                                GLenum type
                        );

                static GLint CreateProgramFromSource
                        (
                                const char* vertex_source,
                                const char* fragment_source
                        );

                virtual void Bind()const;
                virtual void UnBind()const;
                virtual void Upload(const float* wlp_matrix, const Material& material)const;

                Type GetType()const{return type_;}

            protected:
                const GLchar *vertex_source_;
                const GLchar *fragment_source_;
                GLuint program_;
                Type type_;
            };
        }
    }
}

using ShaderType = rew::system::renderer::Shader::Type;


#endif //PRIMITIVEMONSTER03_SHADER_H
