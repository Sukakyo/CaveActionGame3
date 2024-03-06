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
#include "tilemap.h"
#include "tilecollider2d.h"

#include "image_projecter.h"
#include "collider_manager.h"

#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY



using namespace Eigen;



class Field{
	public:
	enum Tag{
		Player, Enemy, Boss, Decoy,
	};

	private:
		std::string name;
		component::CAT_Transform transform;
		int m_layer;
		Tag tag;

		//component::CAT_Image* image;
		component::CAT_Tilemap* tilemap;
		component::CAT_Rigidbody* rigidbody;
		component::CAT_TileCollider2D* tileCollider;


	public:
		std::string get_name();
		Vector3d get_position();
		void print_data();
		void set_scale(const Vector3d scale);
		void project();
		void addForce(const Vector3d force);
		void gain(const float deltaTime);
		void move(const Vector3d new_position);

		component::CAT_Tilemap* get_tilemap();
		component::CAT_Rigidbody* get_rigidbody();
		component::CAT_TileCollider2D* get_tilecollider();
		
		Field(const std::string init_name,const Vector3d init_position,SDL_Renderer*const renderer, ImageProjecter* projecter_ptr, ColliderManager* collider_manager);
		~Field();
};


