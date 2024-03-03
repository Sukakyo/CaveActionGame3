#include "field.h"

#include <eigen3/Eigen/Core>
#include <string>
#include <cstdio>
#include <iostream>
//#include <math.h>

#include "debug_log.h"

#define MASS (2.0)

using namespace std;
using namespace Eigen;

// オブジェクトの名前を取得
string Field::get_name(){
	return this->name;
}

// オブジェクトの位置を取得
Vector3d Field::get_position(){
	return this->transform.get_position();
}

// オブジェクトの任意の情報を出力
void Field::print_data(){
	printf("-----GameObject-----\n");
	printf("tag: %d\n",this->tag);
	printf("name: %s\n", this->name.c_str());
	debug::print("position",this->transform.get_position());
	debug::print("rotation",this->transform.get_rotation());
	debug::print("scale",this->transform.get_scale());
	cout << this->tag << endl;
	printf("-----/GameObject-----\n");

}

// オブジェクトの位置を変更
void Field::move(const Vector3d new_position){
	this->transform.set_position(new_position);
}

void Field::project(){
	this->tilemap->project();
}

void Field::addForce(const Vector3d force){
	this->rigidbody->addForce(force);
}

void Field::gain(const float delta_time){
	this->rigidbody->gain(delta_time);
}

void Field::set_scale(const Vector3d scale){
	this->transform.set_scale(scale);
}

component::CAT_Tilemap* Field::get_tilemap(){
	return this->tilemap;
}

component::CAT_Rigidbody* Field::get_rigidbody(){
	return this->rigidbody;
}

component::CAT_TileCollider2D* Field::get_tilecollider(){
	return this->tileCollider;
}



// コンストラクタ
Field::Field(const string init_name,const Vector3d init_position, SDL_Renderer*const renderer, ImageProjecter* projecter_ptr){
	this->name = init_name;
	this->transform.set_position(init_position);

	this->tilemap = new component::CAT_Tilemap(&(this->transform), "./resource/imgs/tilemap1.png", "./resource/tilemaps/tilemap1_init.csv", renderer);

	projecter_ptr->save(this->tilemap, 1);

	this->rigidbody = new component::CAT_Rigidbody(&(this->transform), component::Newton, MASS);
	this->tileCollider = new component::CAT_TileCollider2D(&(this->transform), this->rigidbody, 0,32,"./resource/tilemaps/tilemap1_collider.csv");
}

// デストラクタ
Field::~Field(){
	printf("Destroy %s!\n",this->name.c_str());
	delete this->tilemap;
	delete this->rigidbody;
	delete this->tileCollider;
}
