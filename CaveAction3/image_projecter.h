#pragma once

#include <vector>

#include "raw_image.h"

#define MAX_IMAGE_LAYER_SIZE (64)


class ImageProjecter {
private:
	std::vector<std::vector<component::CAT_RawImage*>> image_table;

public:

	ImageProjecter();
	~ImageProjecter();

	void save(component::CAT_RawImage* rawImage, unsigned char layer);
	void project();

};