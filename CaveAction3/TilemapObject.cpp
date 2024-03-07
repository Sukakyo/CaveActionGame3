#include "TilemapObject.h"

namespace object {

	TilemapObject::TilemapObject(TilemapObject::ObjectInitializer objectInit) 
	: GameObject::GameObject({
		objectInit.position,
		objectInit.rotation,
		objectInit.scale
		}) {

		this->tilemap = new component::CAT_Tilemap(this->transform,
													objectInit.tilemap_file_path,
													objectInit.tilemap_init,
													objectInit.renderer);

		objectInit.projecter->save(this->tilemap, objectInit.image_layer);

		this->tile_collider = new component::CAT_TileCollider2D(
			this->transform,
			nullptr,
			objectInit.collider_layer,
			objectInit.collider_width,
			objectInit.tilemap_collider_init,
			objectInit.collision_magnitude,
			objectInit.collision
		);

		objectInit.collider_manager->save(this->tile_collider, objectInit.collider_layer);

	}

	TilemapObject::~TilemapObject() {

	}

}