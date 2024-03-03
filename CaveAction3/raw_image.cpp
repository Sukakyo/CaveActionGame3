#include "raw_image.h"

namespace component {

	CAT_RawImage::CAT_RawImage(CAT_Transform* const transform) {
		this->m_transform = transform;
	};

	void CAT_RawImage::project() {};

	double CAT_RawImage::get_position_height() {
		return this->m_transform->get_position()[1];
	}

	bool CAT_RawImage::cmp(CAT_RawImage* a, CAT_RawImage* b) {

		if (a != nullptr && b != nullptr) {

			return a->get_position_height() < b->get_position_height();
		}
		else {
			return false;
		}
	}
}