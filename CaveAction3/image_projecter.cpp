#include "image_projecter.h"

#include "image.h"
#include "animation_image.h"
#include "tilemap.h"


ImageProjecter::ImageProjecter() {
	this->image_table = std::vector<std::vector<component::CAT_RawImage*>>(MAX_LAYER_SIZE);
}

ImageProjecter::~ImageProjecter() {
	for (int i = 0; i < this->image_table.size(); i++) {
		for (int j = 0; j < this->image_table[i].size(); j++) {
			//delete this->image_table[i][j];
		}
	}
}

void ImageProjecter::save(component::CAT_RawImage* rawImage, unsigned char layer){
	this->image_table[layer].push_back(rawImage);
}

void ImageProjecter::project() {
	for (int i = 0; i < this->image_table.size(); i++) {

		std::sort(this->image_table[i].begin(), this->image_table[i].end(), component::CAT_RawImage::cmp);


		for (int j = 0; j < this->image_table[i].size(); j++) {
			this->image_table[i][j]->project();	
		}
	}
}