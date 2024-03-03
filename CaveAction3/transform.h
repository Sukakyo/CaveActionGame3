#pragma once
#include <eigen3/Eigen/Core>

#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY
#include <cstdio>

using namespace Eigen;

namespace component {

	class CAT_Transform {
	private:
		Vector3d m_position = { 0, 0, 0 }; // ˆÊ’u
		Vector3d m_rotation = { 0, 0, 0 };
		Vector3d m_scale    = { 1, 1, 1 };

	public:
		CAT_Transform();
		~CAT_Transform();
		void set_position(const Vector3d vec) { m_position = vec; };
		void set_rotation(const Vector3d vec) { m_rotation = vec; };
		void set_scale(const Vector3d vec) { m_scale = vec; };
		Vector3d get_position() { return m_position; };
		Vector3d get_rotation() { return m_rotation; };
		Vector3d get_scale() { return m_scale; }
	};
}
