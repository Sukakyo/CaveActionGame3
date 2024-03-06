#pragma once

namespace component {

	class CAT_AnimationRoot {
	protected:
		unsigned short state_id = 0;

	public:
		virtual int change_animation(unsigned short new_id);

	};
}