//
// Created by vantan on 2016/02/14.
//

#ifndef PRIMITIVEMONSTER03_MESH_H
#define PRIMITIVEMONSTER03_MESH_H

#include "../../Object.h"
#include "../../../../../../../../../AppData/Local/Android/sdk/ndk-bundle/platforms/android-21/arch-mips/usr/include/GLES3/gl31.h"

#include <vector>

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            class Mesh : public Object
            {
            public:
                Mesh();

                inline const std::vector<float>& GetVertices()const{return vertices_;}
                inline const std::vector<GLuint>& GetIndices()const{return indices_;}
                inline const std::vector<GLuint>& GetWireIndices()const{return wire_indices_;}
                inline GLuint GetSize()const{return indices_.size();}

            protected:
                std::vector<float>vertices_;
                std::vector<GLuint>indices_;
                std::vector<GLuint>wire_indices_;
            };
        }
    }
}



#endif //PRIMITIVEMONSTER03_MESH_H
