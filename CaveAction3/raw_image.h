#pragma once

#include "transform.h"

namespace component {

	class CAT_RawImage {
	protected:
		CAT_Transform* m_transform;
	public:
		CAT_RawImage(CAT_Transform* const transform);
		virtual void project();

		double get_position_height();

		static bool cmp(CAT_RawImage* a, CAT_RawImage* b);
	};
}