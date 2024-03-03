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


void GameObject::addForce(const Vector3d force){
	this->rigidbody->addForce(force);
}

void GameObject::gain(const float delta_time){
	this->virtual_controller->gain(delta_time);
	this->rigidbody->gain(delta_time);
	this->image->gain(delta_time);
}

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
GameObject::GameObject(const string init_name,const Vector3d init_position, SDL_Renderer*const renderer, ImageProjecter* projecter_ptr){
	this->name = init_name;
	this->transform.set_position(init_position);

	this->image = new component::CAT_AnimationImage(&(this->transform), 
	player_anim_1(),
	renderer);

	projecter_ptr->save(this->image, 2);

	
	this->rigidbody = new component::CAT_Rigidbody(&(this->transform), component::Newton, MASS * 2);
	this->virtual_controller = new component::CAT_VirtualController(this->rigidbody, M_PI);
	this->virtual_controller->set_max_speed(150.0);

	this->box_collider = new component::CAT_BoxCollider2D(&(this->transform), this->rigidbody, 0,24,64,Vector2d(0,0));

	
}

// デストラクタ //
GameObject::~GameObject(){
	printf("Destroy %s!\n",this->name.c_str());
	delete this->image;
	delete this->rigidbody;
	delete this->virtual_controller;
	delete this->box_collider;
}
