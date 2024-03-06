#include "game_object.h"
#include <eigen3/Eigen/Core>
#include <string>
#include <cstdio>
#include <iostream>

#include "debug_log.h"
#include "raw_image.h"

#include "PlayerAnim1.h"

#define MASS (2.0)

using namespace std;
using namespace Eigen;

// オブジェクトの名前を取得 //
string GameObject::get_name(){
	return this->name;
}

// オブジェクトの位置を取得 //
Vector3d GameObject::get_position(){
	return this->transform.get_position();
}

// オブジェクトの任意の情報を出力 //
void GameObject::print_data(){
	printf("-----GameObject-----\n");
	printf("tag: %d\n",this->tag);
	printf("name: %s\n", this->name.c_str());
	debug::print("position",this->transform.get_position());
	debug::print("rotation",this->transform.get_rotation());
	debug::print("scale",this->transform.get_scale());
	cout << this->tag << endl;
	printf("-----/GameObject-----\n");

}

// オブジェクトの位置を変更 //
void GameObject::move(const Vector3d new_position){
	this->transform.set_position(new_position);
}

void GameObject::input(const Vector3d input){
	this->virtual_controller->input(input);
}

void GameObject::project(){
	this->image->project();
}

void GameObject::change_anim(unsigned short new_id) {
	this->image->change_animation(new_id);
}

void GameObject::save_animation(unsigned short index, Vector2i* direction, unsigned short animation_id) {

	unsigned short vector_key;

	if (direction != nullptr) {
		if (*direction == Eigen::Vector2i(0, 1)) {
			vector_key = 0;
		}
		else if (*direction == Eigen::Vector2i(-1, 0)) {
			vector_key = 1;
		}
		else if (*direction == Eigen::Vector2i(1, 0)) {
			vector_key = 2;
		}
		else if (*direction == Eigen::Vector2i(0, -1)) {
			vector_key = 3;
		}
	}

	this->animator->save(index, vector_key, animation_id);
}

void GameObject::change_animation(unsigned short index, Vector2i* direction) {
	this->animator->change_animation(index, direction);
}

void GameObject::addForce(const Vector3d force){
	this->rigidbody->addForce(force);
}

void GameObject::gain(const float delta_time){
	this->player_controller->update();
	this->virtual_controller->gain(delta_time);
	this->rigidbody->gain(delta_time);
	this->image->gain(delta_time);

	this->player_controller->gain(delta_time);
}

void GameObject::set_input(CAT_Input* const new_input) {
	this->player_controller->set_input(new_input);
};

void GameObject::set_scale(const Vector3d scale){
	this->transform.set_scale(scale);
}

component::CAT_AnimationImage* GameObject::get_image(){
	return this->image;
}

component::CAT_Rigidbody* GameObject::get_rigidbody(){
	return this->rigidbody;
}

component::CAT_VirtualController* GameObject::get_virtual_controller(){
	return this->virtual_controller;
}

component::CAT_BoxCollider2D* GameObject::get_box_collider_2d(){
	return this->box_collider;
}


// コンストラクタ //
GameObject::GameObject(const string init_name,const Vector3d init_position, SDL_Renderer*const renderer, ImageProjecter* projecter_ptr, ColliderManager* collider_manager){
	this->name = init_name;
	this->transform.set_position(init_position);

	this->image = new component::CAT_AnimationImage(&(this->transform), 
	player_anim_1(),
	renderer);

	this->animator = new component::CAT_Animator2D(this->image);

	unsigned short down = 0;
	unsigned short left = 1;
	unsigned short right = 2;
	unsigned short up = 3;
	this->animator->save(0, down , 0);
	this->animator->save(0, left , 1);
	this->animator->save(0, right, 2);
	this->animator->save(0, up,    3);
	this->animator->save(1, down,  4);
	this->animator->save(1, left,  5);
	this->animator->save(1, right, 6);
	this->animator->save(1, up,    7);
	this->animator->save(2, down,  8);
	this->animator->save(2, left,  9);
	this->animator->save(2, right,10);
	this->animator->save(2, up,   11);


	projecter_ptr->save(this->image, 2);

	
	this->rigidbody = new component::CAT_Rigidbody(&(this->transform), component::CAT_Rigidbody::Newton, MASS * 2);
	this->virtual_controller = new component::CAT_VirtualController(this->rigidbody, M_PI);
	this->virtual_controller->set_max_speed(150.0);

	this->box_collider = new component::CAT_BoxCollider2D(&(this->transform), this->rigidbody, 0,24,64,Vector2d(0,0));

	collider_manager->save(this->box_collider, 0);

	this->player_controller = new component::PlayerController(this->rigidbody, this->virtual_controller, this->animator);

}

// デストラクタ //
GameObject::~GameObject(){
	printf("Destroy %s!\n",this->name.c_str());
	delete this->image;
	delete this->rigidbody;
	delete this->virtual_controller;
	delete this->box_collider;
	delete this->animator;

	delete this->player_controller;
}
