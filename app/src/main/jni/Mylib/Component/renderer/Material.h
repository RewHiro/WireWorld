//
// Created by vantan on 2016/02/14.
//

#ifndef PRIMITIVEMONSTER03_MATERIAL_H
#define PRIMITIVEMONSTER03_MATERIAL_H

#include "../../Object.h"
#include "Color.h"
#include "Shader.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            class Material : public Object
            {
            public:
                Material
                        (
                                Shader::Type type = Shader::Type::BASIC ,
                                float red = 1.0f,
                                float green = 1.0f,
                                float blue = 1.0f,
                                float alpha = 1.0f,
                                unsigned int indices_num = 0
                        );
                Color<float> GetColor()const{return color_;}
                ShaderType GetShaderType()const{return shader_type_;}
                unsigned int GetIndicesNum()const{return indices_num_;}

                Material SetColor(const Color<float>& color){color_ = color; return *this;}

            private:
                Color<float>color_;
                ShaderType shader_type_;
                unsigned int indices_num_;
            };
        }
    }
}



#endif //PRIMITIVEMONSTER03_MATERIAL_H
