//
// Created by vantan on 2016/02/16.
//

#include "Sphere.h"

#include "../../Eigen/Core"
#include "../../Eigen/Geometry"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            Sphere::Sphere():
            Mesh()
            {
                std::vector<Eigen::Vector3f> vertices;

                int slice = 10;

                float add_radian = M_PI * 2.0f / slice;

                for(float i = add_radian; i < M_PI; i += add_radian)
                {
                    float temp_y = std::cosf(i);
                    float r = std::sinf(i);

                    for (float j = 0.0f; j < M_PI * 2; j += add_radian)
                    {
                        float temp_x = r * std::cosf(j);
                        float temp_z = r * std::sinf(j);
                        vertices.emplace_back(temp_x, temp_y, temp_z);
                    }
                }

                vertices.emplace_back(0, 1, 0);
                vertices.emplace_back(0, -1, 0);

                for(int i = 0; i < vertices.size(); i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        vertices_.emplace_back(vertices.data()[i].data()[j]);
                    }
                }

                std::vector<GLuint>indices;

                for(int i = 1; i < slice / 2 - 1; i++)
                {
                    for(int j = 0; j < slice; j++)
                    {
                        indices.emplace_back((j + 1) % slice + i * slice);
                        indices.emplace_back(j + i * slice);
                        indices.emplace_back(j + (i - 1) * slice);

                        indices.emplace_back((j + 1) % slice + (i - 1) * slice);
                        indices.emplace_back((j + 1) % slice + i * slice);
                        indices.emplace_back(j + (i - 1) * slice);

                    }
                }


                for(int i = 0; i < slice; i++)
                {
                    indices.emplace_back(vertices.size() - 2);
                    indices.emplace_back(i);
                    indices.emplace_back((i + 1) % slice);

                    int num = slice / 2 - 2;
                    indices.emplace_back(i + num * slice);
                    indices.emplace_back(vertices.size() - 1);
                    indices.emplace_back((i + 1) % slice + num * slice);
                }

                indices_ = indices;

                std::vector<GLuint>wire_indices;

                for(int i = 1; i < slice / 2 - 1; i++)
                {
                    for(int j = 0; j < slice; j++)
                    {
                        wire_indices.emplace_back(j + (i - 1) * slice);
                        wire_indices.emplace_back(j + i * slice);
                    }
                }

                for(int i = 0; i < slice; i++)
                {
                    wire_indices.emplace_back(vertices.size() - 2);
                    wire_indices.emplace_back(i);
                }


                for(int i = 0; i < slice; i++)
                {
                    wire_indices.emplace_back(i + ((slice / 2) - 2) * slice);
                    wire_indices.emplace_back(vertices.size() - 1);
                }


                for(int i = 1; i < slice / 2 - 1; i++)
                {
                    for (int j = 0; j < slice; j++)
                    {

                        int test = j + ((i - 1) * slice);
                        int testa = (j + ((i - 1) * slice) + 1) % (i * slice);
                        wire_indices.emplace_back(j + ((i - 1) * slice));
                        wire_indices.emplace_back((j + 1) % slice + (i - 1) * slice);
                    }
                }

                wire_indices_ = wire_indices;
            }
        }
    }
}