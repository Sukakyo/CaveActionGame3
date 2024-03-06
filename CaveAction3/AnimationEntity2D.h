#pragma once

#include "GameObject.h"

#include "animation_image.h"
#include "animator2d.h"
#include "rigidbody.h"
#include "boxcollider2d.h"
#include "virtual_controller.h"

#include <vector>

#include "image_projecter.h"

namespace object {
	class AnimationEntity2D : public GameObject {
	protected:
		component::CAT_AnimationImage* animation_image;
		component::CAT_Animator2D* animator_2d;
		component::CAT_Rigidbody* rigidbody;
		component::CAT_BoxCollider2D* box_collider;
		component::CAT_VirtualController* virtual_contoroller;

	public:
		struct ObjectInitializer : GameObject::ObjectInitializer{
			const char* animation_data; /* AnimationImage */
			SDL_Renderer* renderer;
			unsigned short image_layer;
			ImageProjecter* projecter;

			std::vector<std::tuple<unsigned short, unsigned short, unsigned short>> animation_sets;
			component::CAT_Rigidbody::Type physics_type;
			float mass;


			float input_speed;
			float max_speed;


			unsigned short collider_layer;
			float collider_w;
			float collider_h;
			Vector2d collider_offset;


		};

		AnimationEntity2D(AnimationEntity2D::ObjectInitializer objectInit);
		virtual ~AnimationEntity2D();

	};

}