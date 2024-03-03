#pragma once

#include <eigen3/Eigen/Dense>

#define EIGEN_NO_DEBUG
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY

#include "transform.h"
#include "rigidbody.h"

#define DEFAULT_MAGNITUDE (4500)
#define DEFAULT_COLLISION (1)

namespace component
{

    class CAT_Collider2D
    {
    protected:
        unsigned short m_layer;
        CAT_Transform* m_transform;
        CAT_Rigidbody* m_rigidbody;
        float m_force_magnitude;
        int m_collision;

    public:
        CAT_Collider2D(CAT_Transform* transform, 
                        CAT_Rigidbody* const rigidbody = nullptr, 
                        const unsigned short layer = 0, 
                        const float magnitude = DEFAULT_MAGNITUDE,
                        const int collision = DEFAULT_COLLISION);
        virtual int judge(CAT_Collider2D *collider);
        virtual void update();
        unsigned short get_layer();
        int get_collision();
        void add_force(Eigen::Vector3d force);
        Eigen::Vector3d get_velocity();
    };

}
