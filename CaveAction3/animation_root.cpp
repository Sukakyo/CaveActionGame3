#include "animation_root.h"

namespace component {

	int CAT_AnimationRoot::change_animation(unsigned short new_id) {
		this->state_id = new_id;
		return 0;
	}
}