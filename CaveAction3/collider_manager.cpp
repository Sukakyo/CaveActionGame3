#include "collider_manager.h"

#include <vector>

ColliderManager::ColliderManager() {
	this->collider_table = std::vector<std::vector<component::CAT_Collider2D*>>(MAX_COLLIDER_LAYER_SIZE);
}

ColliderManager::~ColliderManager() {

}

void ColliderManager::save(component::CAT_Collider2D* collider, unsigned char layer) {
	this->collider_table[layer].push_back(collider);
}

void ColliderManager::judge() {
	for (int i = 0; i < this->collider_table.size(); i++) {
		for (int j = 0; j < this->collider_table[i].size(); j++) {
			this->collider_table[i][j]->update();
			for (int k = 0; k < this->collider_table[i].size(); k++) {
				if (k != j) {
					this->collider_table[i][j]->judge(this->collider_table[i][k]);
				}
			}
		}
	}
}