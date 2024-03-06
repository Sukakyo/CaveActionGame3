#include "GameObject.h"

namespace object {

	GameObject::GameObject(GameObject::ObjectInitializer objectInit) {
		this->transform = new component::CAT_Transform();

		this->transform->set_position(objectInit.position);
		this->transform->set_rotation(objectInit.rotation);
		this->transform->set_scale(objectInit.scale);
	}

	GameObject::~GameObject() {
		delete this->transform;
	}

	void GameObject::Update() {

	}

	void GameObject::Gain(double delta_time) {

	}
}