#pragma once


#include <eigen3/Eigen/Core>
#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY

#include "virtual_controller.h"
#include "rigidbody.h"
#include "animator2d.h"

#include "shared_struct.h"

namespace component {

	class PlayerController {
	private:
		CAT_Input* m_input = nullptr;
		CAT_Rigidbody* m_rigidbody;
		CAT_VirtualController* m_virtual_controller;

		CAT_Animator2D* m_animator2D;

		Eigen::Vector2d tmp_direction;

		enum PlayerState {
			Move,
			Attack
		};

		PlayerState state = PlayerState::Move;

		double sum_time = 0;

	private:
		void change_state(PlayerState new_state);
		

	public:
		PlayerController(CAT_Rigidbody*const new_rigidbody,CAT_VirtualController*const new_v_controller,CAT_Animator2D*const new_animator2D);
		void set_input(CAT_Input* const new_input);
		void update();
		void gain(double delta_time);
	};
}