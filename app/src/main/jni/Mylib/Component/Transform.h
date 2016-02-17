//
// Created by vantan on 2016/02/12.
//

#ifndef PRIMITIVEMONSTER03_TRANSFORM_H
#define PRIMITIVEMONSTER03_TRANSFORM_H

#include "Component.h"

#include <list>

#include "../Eigen/Core"
#include "../Eigen/Geometry"

namespace rew {
    namespace system {
        class Transform : public Component, public std::enable_shared_from_this<Transform> {
        public:
            explicit Transform
                    (
                            GameObject& game_object,
                            const Eigen::Vector3f& pos = Eigen::Vector3f::Zero(),
                            const Eigen::Vector3f& scale = Eigen::Vector3f::Ones(),
                            const Eigen::Quaternionf rotate = Eigen::Quaternionf::Identity()
                    );

            // Getter
            inline const Eigen::Vector3f& GetPos() const { return position_; }

            inline const Eigen::Vector3f& GetScale() const { return scale_; }

            inline const Eigen::Quaternionf& GetRotate() const { return rotate_; }

            inline const std::shared_ptr<Transform> &GetParent() const { return parent_; }

            Eigen::Matrix4f GetWorldMatrix() const
            {
                auto translation = Eigen::Translation3f(position_);
                auto scaling = Eigen::AlignedScaling3f(scale_);

                Eigen::Affine3f affine = translation * rotate_ * scaling;

                return affine.matrix();
            }

            Eigen::Vector3f GetDirection()const
            {
                return rotate_ * -Eigen::Vector3f::UnitZ();
            }

            // Setter
            inline Transform* const SetPos(const Eigen::Vector3f &pos) {
                position_ = pos;
                return this;
            }

            inline Transform* const SetScale(const Eigen::Vector3f &scale) {
                scale_ = scale;
                return this;
            }

            inline Transform* const SetRotate(const Eigen::Quaternionf &rotate) {
                rotate_ = rotate;
                return this;
            }

            inline Transform* const Translate(const Eigen::Vector3f &pos) {
                position_ += pos;
                return this;
            }

            inline Transform* const Scale(const Eigen::Vector3f &scale) {
                scale_ += scale;
                return this;
            }

            inline Transform* const Rotation(const Eigen::Quaternionf &rotate) {
                rotate_ *= rotate;
                return this;
            }

            inline Transform* const SetParent
                    (
                            const std::shared_ptr<Transform> &parent
                    ) {
                children_.emplace_back(shared_from_this());
                parent_ = parent;
                return this;
            }

        private:

            void Update()override;

            std::list<std::shared_ptr<Transform>const> children_;
            Eigen::Vector3f position_;
            Eigen::Vector3f scale_;
            Eigen::Quaternionf rotate_;
            std::shared_ptr<Transform> parent_;

        };
    }
}
#endif //PRIMITIVEMONSTER03_TRANSFORM_H
