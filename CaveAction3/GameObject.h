#pragma once

#include <eigen3/Eigen/Dense>

#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY

#include "transform.h"

namespace object {

	class GameObject {
	protected:
		component::CAT_Transform* transform;

	public:

		struct ObjectInitializer {
			Vector3d position;
			Vector3d rotation;
			Vector3d scale;

		};

		GameObject(GameObject::ObjectInitializer objectInit);
		virtual ~GameObject();

		Vector3d GetPosition() { return transform->get_position(); }
		Vector3d GetRotation() { return transform->get_rotation(); }

	};
}