#pragma once
#include <eigen3/Eigen/Core>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "transform.h"
#include "rigidbody.h"
#include "virtual_controller.h"
#include "image.h"
#include "boxcollider2d.h"
#include "animation_image.h"


#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY



//using namespace std;
using namespace Eigen;



class GameObject{
	public:
		enum Tag{
			Player, Enemy, Boss, Decoy,
		};

	private:
		std::string name;
		component::CAT_Transform transform;
		int m_layer;
		Tag tag;

		component::CAT_AnimationImage* image;
		component::CAT_Rigidbody* rigidbody;
		component::CAT_VirtualController* virtual_controller;
		component::CAT_BoxCollider2D* box_collider;



	public:
		std::string get_name();
		Vector3d get_position();
		void print_data();
		void set_scale(const Vector3d scale);
		void project();
		void addForce(const Vector3d force);
		void gain(const float deltaTime);
		void move(const Vector3d new_position);
		void input(const Vector3d input);

		component::CAT_AnimationImage* get_image();
		component::CAT_Rigidbody* get_rigidbody();
		component::CAT_VirtualController* get_virtual_controller();
		component::CAT_BoxCollider2D* get_box_collider_2d();

		GameObject(const std::string init_name,const Vector3d init_position,SDL_Renderer*const renderer, ImageProjecter* projecter_ptr);
		~GameObject();
};


