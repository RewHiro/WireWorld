//
// Created by vantan on 2016/02/14.
//

#include "Camera.h"

#include <cmath>

#include "../GameObject.h"
#include "Transform.h"

namespace rew
{
    namespace system
    {
        Camera::Camera(GameObject &game_object) :
        Component(game_object, "Camera")
        {
            SetName(GetTypeName());

            PerspectiveState perspective_state =
                    {
                            45.0f,
                            400.0f / 800.0f,
                            0.1f,
                            100.0f
                    };
            perspective_state_ = perspective_state;

            OrthogonalState orthogonal_state =
                    {
                            -1.0f, 1.0f,
                            1.0f, -1.0f,
                            0.1f, 100.0f
                    };
            orthogonal_state_ = orthogonal_state;
        }

        Eigen::Matrix4f Camera::Perspective()const
        {
            Eigen::Matrix4f mat = Eigen::Matrix4f::Zero();

            float fov_radian = 1.0f / std::tanf(perspective_state_.field_of_view_ * 0.5f * M_PI / 180.0f);
            float dz = perspective_state_.far_ - perspective_state_.near_;

            mat(0, 0) = fov_radian / perspective_state_.aspect_;
            mat(1, 1) = fov_radian;
            mat(2, 2) = -(perspective_state_.far_ + perspective_state_.near_) / dz;
            mat(2, 3) = -(2 * perspective_state_.far_ * perspective_state_.near_) / dz;
            mat(3, 2) = -1;

            return mat;
        }

        Eigen::Matrix4f Camera::Orthogonal()const
        {
            float dx = orthogonal_state_.right_ - orthogonal_state_.left_;
            float dy = orthogonal_state_.top_ - orthogonal_state_.bottom_;
            float dz = orthogonal_state_.far_ - orthogonal_state_.near_;

            Eigen::Matrix4f mat;
            mat <<
            2.0f / dx, 0, 0, 0,
            0, 2.0f / dy, 0, 0,
            0, 0, -2.0f / dz, 0,
            -(orthogonal_state_.right_ + orthogonal_state_.left_) / dx, -(orthogonal_state_.top_ + orthogonal_state_.bottom_) / dy , -(orthogonal_state_.far_ + orthogonal_state_.near_) / dz, 1.0f;

            return mat;
        }

        Eigen::Matrix4f Camera::LookAt()const
        {
            Eigen::Vector3f eye(GetGameObject().GetTransform()->GetPos());

            auto rotate = GetGameObject().GetTransform()->GetRotate();

            Eigen::Vector3f direction = rotate * -Eigen::Vector3f::UnitZ();

            Eigen::Vector3f target(eye + direction * 100);
            Eigen::Vector3f up(rotate * Eigen::Vector3f::UnitY());

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

        Camera* const Camera::SetPerspective
                (
                        float field_of_view,
                        float aspect,
                        float near,
                        float far
                )
        {
            perspective_state_.field_of_view_ = field_of_view;
            perspective_state_.aspect_ = aspect;
            perspective_state_.near_ = near;
            perspective_state_.far_ = far;

            return this;
        }

        Camera* const Camera::SetOrthogonal
                (
                        float left,
                        float right,
                        float bottom,
                        float top,
                        float near,
                        float far
                )
        {
            orthogonal_state_.left_ = left;
            orthogonal_state_.right_ = right;
            orthogonal_state_.bottom_ = bottom;
            orthogonal_state_.top_ = top;
            orthogonal_state_.near_ = near;
            orthogonal_state_.far_ = far;

            return this;
        }
    }
}