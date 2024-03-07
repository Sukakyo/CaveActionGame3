#pragma once

#include "AnimationEntity2D.h"

#include "player_controller.h"
#include "shared_struct.h"

namespace object {
	class Player2D : public AnimationEntity2D {
	private:
		component::CAT_PlayerController* player_controller;

	public:

		struct ObjectInitializer : AnimationEntity2D::ObjectInitializer {
			CAT_Input* player_input;
		};

		Player2D(ObjectInitializer objectInit);
		~Player2D();

		void Update() override;
		void Gain(double delta_time) override;

	};


}