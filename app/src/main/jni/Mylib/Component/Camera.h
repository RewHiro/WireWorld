//
// Created by vantan on 2016/02/14.
//

#ifndef PRIMITIVEMONSTER03_CAMERA_H
#define PRIMITIVEMONSTER03_CAMERA_H

#include "Component.h"

#include "../Eigen/Core"
#include "../Eigen/Geometry"

namespace rew
{
    namespace system
    {
        class Camera : public Component
        {
        public:

            struct PerspectiveState
            {
                float field_of_view_;
                float aspect_;
                float near_;
                float far_;
            };

            struct OrthogonalState
            {
                float left_;
                float right_;
                float bottom_;
                float top_;
                float near_;
                float far_;
            };



            explicit Camera(GameObject& game_object);

            Eigen::Matrix4f Perspective()const;
            Eigen::Matrix4f Orthogonal()const;
            Eigen::Matrix4f LookAt()const;

            Camera* const SetPerspective
                    (
                            float field_of_view,
                            float aspect,
                            float near,
                            float far
                    );

            Camera* const SetOrthogonal
                    (
                            float left,
                            float right,
                            float bottom,
                            float top,
                            float near,
                            float far
                    );

        private:
            PerspectiveState perspective_state_;
            OrthogonalState orthogonal_state_;
        };
    }
}


#endif //PRIMITIVEMONSTER03_CAMERA_H
