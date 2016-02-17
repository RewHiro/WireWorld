//
// Created by vantan on 2016/02/07.
//

#ifndef PRIMITIVEMONSTER03_CAMERAMATRIX_H
#define PRIMITIVEMONSTER03_CAMERAMATRIX_H

#include "../Eigen/Core"

namespace camera
{
    Eigen::Matrix4f Perspective(float fovy, float aspect, float near, float far);

    Eigen::Matrix4f LookAt(
            float eye_x, float eye_y, float eye_z,
            float target_x, float target_y, float target_z,
            float up_x, float up_y, float up_z);
}

#endif //PRIMITIVEMONSTER03_CAMERAMATRIX_H
