#pragma once

#include <eigen3/Eigen/Core>
#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY

#include "animation_root.h"
#include <map>

#define DIRECTION_MAX (4)

namespace component {


	class CAT_Animator2D {
	private:
		CAT_AnimationRoot* animation_root;
		std::map<std::pair<unsigned short, unsigned short>, unsigned short> animation_map;


		Eigen::Vector2i direction;

	private:
		unsigned short vector2i_to_key(Eigen::Vector2i* vector);

	public:
		CAT_Animator2D(CAT_AnimationRoot* const anim_root);
		void save(unsigned short index, unsigned short direction, unsigned short animation_id);
		void change_animation(unsigned short index, Eigen::Vector2i* direction);
	};
}