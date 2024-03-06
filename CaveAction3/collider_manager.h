#pragma once

#include "collider2d.h"
#include <vector>

#define MAX_COLLIDER_LAYER_SIZE (64)


class ColliderManager {
private:
	std::vector<std::vector<component::CAT_Collider2D*>> collider_table;

public:
	ColliderManager();
	~ColliderManager();

	void save(component::CAT_Collider2D* collider, unsigned char layer);
	void judge();
};


