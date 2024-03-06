#include "AnimationEntity2D.h"

namespace object {
	AnimationEntity2D::AnimationEntity2D(AnimationEntity2D::ObjectInitializer objectInit) 
	: GameObject::GameObject({objectInit.position, objectInit.rotation, objectInit.scale}) {
		this->animation_image = new component::CAT_AnimationImage(this->transform,objectInit.animation_data,objectInit.renderer);
		this->animator_2d = new component::CAT_Animator2D(this->animation_image);

		objectInit.projecter->save(this->animation_image, objectInit.image_layer);

		for (int i = 0; i < objectInit.animation_sets.size(); i++) {
			this->animator_2d->save(std::get<0>(objectInit.animation_sets[i]), 
									std::get<1>(objectInit.animation_sets[i]), 
									std::get<2>(objectInit.animation_sets[i]));
		}

		this->rigidbody = new component::CAT_Rigidbody(this->transform, objectInit.physics_type, objectInit.mass);

		this->virtual_contoroller = new component::CAT_VirtualController(this->rigidbody, objectInit.input_speed);
		this->virtual_contoroller->set_max_speed(objectInit.max_speed);

		this->box_collider = new component::CAT_BoxCollider2D(this->transform,
			this->rigidbody,
			objectInit.collider_layer,
			objectInit.collider_w,
			objectInit.collider_h,
			objectInit.collider_offset);
		objectInit.collider_manager->save(this->box_collider, objectInit.collider_layer);

	}


	AnimationEntity2D::~AnimationEntity2D(){

		delete this->animation_image;
		delete this->animator_2d;
		delete this->rigidbody;
		delete this->virtual_contoroller;
		delete this->box_collider;

	}

	void AnimationEntity2D::Update() {

	}

	void AnimationEntity2D::Gain(double delta_time) {
		this->virtual_contoroller->input(Eigen::Vector3d(1, 0, 0));

		this->animation_image->gain(delta_time);
		this->rigidbody->gain(delta_time);
		this->virtual_contoroller->gain(delta_time);
	}
}