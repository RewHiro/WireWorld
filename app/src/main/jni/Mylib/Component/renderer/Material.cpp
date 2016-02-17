//
// Created by vantan on 2016/02/14.
//

#include "Material.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            Material::Material
                    (
                            Shader::Type type,
                            float red,
                            float green,
                            float blue,
                            float alpha,
                            unsigned int indices_num
                    ) :
            Object(),
            color_(red, green, blue, alpha),
            shader_type_(type),
            indices_num_(indices_num)
            {
            }
        }
    }
}