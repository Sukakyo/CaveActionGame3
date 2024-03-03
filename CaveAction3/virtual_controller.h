#pragma once
#include <eigen3/Eigen/Core>
#include "rigidbody.h"

#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY

using namespace Eigen;

namespace component
{

	class CAT_VirtualController
	{
	private:
		float m_max_speed;
		float m_periodic_time = 0;
		CAT_Rigidbody *m_rigidbody;
		Vector3d m_real_input;
		Vector3d m_virtual_input;
		float m_hold_time = 0;
		float m_input_speed;

		float update_element(const float element_dest,
							 const float element_present,
							 const float delta_time);
		Vector3d limit(Vector3d velocity, Vector3d input);

	public:
		CAT_VirtualController(CAT_Rigidbody *const rigidbody, const float input_speed);
		void set_max_speed(const float max_speed);
		void set_periodic_time(const float periodic_time);
		void input(const Vector3d input_force);
		void gain(const float delta_time);
	};
}