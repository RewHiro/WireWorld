//
// Created by vantan on 2016/02/11.
//

#include "BasicShader.h"
#include "Material.h"
#include <android/log.h>

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            BasicShader::BasicShader():
                    Shader
                            (
                                    "#version 300 es\n"
                                            "layout(location = 0) in mediump vec4 pos;"
                                            "uniform mediump mat4 wlp_matrix;"
                                            "void main() {"
                                            "   gl_Position = wlp_matrix * pos;"
                                            "}",

                                    "#version 300 es\n"
                                            "out mediump vec4 gl_color;"
                                            "uniform mediump vec4 color;"
                                            "void main() {"
                                            "   gl_color = color;"
                                            "}",
                                    Type::BASIC
                            ),
                    unif_wlp_matrix(glGetUniformLocation(program_, "wlp_matrix")),
                    unif_color(glGetUniformLocation(program_, "color"))
            {

            }

            void BasicShader::Bind()const
            {
                Shader::Bind();
            }

            void BasicShader::UnBind()const
            {
                glDisableVertexAttribArray(0);
            }

            void BasicShader::Upload(const float* wlp_matrix, const Material& material)const
            {
                glEnableVertexAttribArray(0);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

                glUniformMatrix4fv(unif_wlp_matrix, 1, GL_FALSE, wlp_matrix);

                auto color = material.GetColor();
                glUniform4f(unif_color, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
            }
        }
    }
}
