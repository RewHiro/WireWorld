//
// Created by vantan on 2016/02/11.
//

#include "Shader.h"

#include <android/log.h>
#include <cassert>
#include <stdlib.h>

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            Shader::Shader
                    (
                            const char* vertex_source,
                            const char* fragment_source,
                            Type type
                    ):
                    vertex_source_(vertex_source),
                    fragment_source_(fragment_source),
                    program_(CreateProgramFromSource(vertex_source, fragment_source)),
                    type_(type)
            {
                assert(glGetError() == GL_NO_ERROR);
                assert(program_ != 0);
            }

            Shader::~Shader()
            {
                glDeleteProgram(program_);
            }

            GLint Shader::LoadShader(
                    const char *source,
                    GLenum type)
            {
                const GLint shader = glCreateShader(type);
                assert(glGetError() == GL_NO_ERROR);

                glShaderSource(shader, 1, &source, NULL);
                glCompileShader(shader);

                GLint compile_success = 0;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_success);

                if(compile_success == GL_FALSE)
                {
                    GLint info_len = 0;
                    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
                    if(info_len > 1)
                    {
                        GLchar* message = reinterpret_cast<GLchar*>(calloc(info_len, sizeof(GLchar)));
                        glGetShaderInfoLog(shader, info_len, NULL, message);
                        __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", message);
                        free(message);
                    }
                    else
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "compile error not info ...");
                    }
                }

                assert(compile_success == GL_TRUE);

                return shader;
            }

            GLint Shader::CreateProgramFromSource
                    (
                            const char* vertex_source,
                            const char* fragment_source
                    )
            {
                const GLuint vertex_shader = LoadShader(vertex_source, GL_VERTEX_SHADER);
                const GLuint fragment_shader = LoadShader(fragment_source, GL_FRAGMENT_SHADER);

                const GLuint program = glCreateProgram();
                assert(glGetError() == GL_NO_ERROR);
                assert(program != 0);

                glAttachShader(program, vertex_shader);
                glAttachShader(program, fragment_shader);
                assert(glGetError() == GL_NO_ERROR);

                glLinkProgram(program);

                GLint link_success = 0;
                glGetProgramiv(program, GL_LINK_STATUS, &link_success);

                if(link_success == GL_FALSE)
                {
                    GLint info_len = 0;
                    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);

                    if(info_len > 1)
                    {
                        GLchar* message = reinterpret_cast<GLchar*>(calloc(info_len, sizeof(GLchar)));
                        glGetProgramInfoLog(program, info_len, NULL, message);
                        __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", message);
                        free(message);
                    }
                }

                assert(link_success == GL_TRUE);

                glDeleteShader(vertex_shader);
                glDeleteShader(fragment_shader);

                return program;
            }

            void Shader::Bind()const
            {
                glUseProgram(program_);
            }

            void Shader::UnBind()const
            {
                glUseProgram(0);
            }

            void Shader::Upload(const float* wlp_matrix, const Material& material)const
            {

            }
        }
    }
}

