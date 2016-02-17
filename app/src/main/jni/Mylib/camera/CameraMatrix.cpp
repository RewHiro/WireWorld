//
// Created by vantan on 2016/02/07.
//

#include "CameraMatrix.h"

#define _USE_MATH_DEFINES

#include <cmath>

#include "../Eigen/Geometry"

namespace camera
{
    Eigen::Matrix4f Perspective(float fovy, float aspect, float near, float far)
    {
        Eigen::Matrix4f mat = Eigen::Matrix4f::Zero();

        float fov_radian = 1.0f / std::tanf(fovy * 0.5f * M_PI / 180.0f);
        float dz = far - near;

        mat(0, 0) = fov_radian / aspect;
        mat(1, 1) = fov_radian;
        mat(2, 2) = -(far + near) / dz;
        mat(2, 3) = -(2 * far * near) / dz;
        mat(3, 2) = -1;

        return mat;
    }

    Eigen::Matrix4f LookAt(
            float eye_x, float eye_y, float eye_z,
            float target_x, float target_y, float target_z,
            float up_x, float up_y, float up_z)
    {
        Eigen::Vector3f eye(eye_x, eye_y, eye_z);
        Eigen::Vector3f target(target_x, target_y, target_z);
        Eigen::Vector3f up(up_x, up_y, up_z);

        Eigen::Vector3f diff = eye- target;
        float distance = diff.norm();

        Eigen::Vector3f z = diff / distance;

        Eigen::Vector3f up_cross = up.cross(z);

        Eigen::Vector3f x = up_cross / up_cross.norm();

        Eigen::Vector3f y = z.cross(x);

        Eigen::Matrix4f r;
        r <<
            x.x(), x.y(), x.z(), 0,
            y.x(), y.y(), y.z(), 0,
            z.x(), z.y(), z.z(), 0,
            0, 0, 0, 1;

        Eigen::Matrix4f t;
        t <<
        1, 0, 0, -eye.x(),
        0, 1, 0, -eye.y(),
        0, 0, 1, -eye.z(),
        0, 0, 0, 1;

        return (r * t);
    }
}