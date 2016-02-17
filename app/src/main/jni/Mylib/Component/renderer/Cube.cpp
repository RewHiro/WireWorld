//
// Created by vantan on 2016/02/14.
//

#include "Cube.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            Cube::Cube():
            Mesh()
            {
                vertices_ =
                        {
                                -0.5f, -0.5f, 0.5f, //0　左下
                                -0.5f, 0.5f, 0.5f, //1　左上
                                0.5f, -0.5f, 0.5f, //2　右下
                                0.5f, 0.5f, 0.5f, //3　右上

                                -0.5f, -0.5f, -0.5f, //4　左下
                                -0.5f, 0.5f, -0.5f, //5　左上
                                0.5f, -0.5f, -0.5f, //6　右下
                                0.5f, 0.5f, -0.5f //7　右上
                        };
                vertices_.shrink_to_fit();


                indices_ =
                        {
                                2, 1, 0,
                                2, 3, 1,

                                4, 5, 6,
                                5, 7, 6,

                                6, 3, 2,
                                7, 3, 6,

                                0, 5, 4,
                                0, 1, 5,

                                3, 5, 1,
                                3, 7, 5,

                                6, 0, 4,
                                6, 2, 0
                        };
                indices_.shrink_to_fit();

                wire_indices_ =
                        {
                                1, 3,
                                3, 2,
                                2, 0,
                                0, 1,

                                5, 7,
                                7, 6,
                                6, 4,
                                4, 5,

                                3, 7,
                                7, 6,
                                6, 2,
                                2, 3,

                                1, 5,
                                5, 4,
                                4, 0,
                                0, 1,

                                5, 7,
                                7, 3,
                                3, 1,
                                1, 5,

                                0, 2,
                                2, 6,
                                6, 4,
                                4, 0
                        };
                    wire_indices_.shrink_to_fit();

            }
        }
    }
}