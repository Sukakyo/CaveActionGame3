#include "animation_image.h"

#include "image_storage.h"

#include "debug_log.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace component
{

	CAT_AnimationImage::CAT_AnimationImage(CAT_Transform *const transform, std::vector<const char *> paths, std::vector<double> durations, SDL_Renderer *const renderer)
		:CAT_RawImage(transform) {
		debug::debugLog("Create Image!\n");
		
		CAT_ImageStorage *storage = CAT_ImageStorage::getInstance();

		this->m_renderer = renderer;



		double sum_time = 0;
		for (int i = 0; i < durations.size(); i++){
			sum_time += durations[i];
			this->state.duration_times.push_back(sum_time);
		}

		for (int i = 0; i < paths.size(); i++)
		{
			storage->save_image(paths[i]);
			this->state.m_images.push_back(storage->get_image(paths[i]));
			

			if (!this->state.m_images[i])
			{
				debug::debugLog("IMG_Load: %s\n", IMG_GetError());
			}

			SDL_SetColorKey(this->state.m_images[i],
							SDL_TRUE,
							SDL_MapRGB(this->state.m_images[i]->format, 255, 0, 255));

			this->state.m_textures.push_back( SDL_CreateTextureFromSurface(m_renderer, this->state.m_images[i]));

			SDL_QueryTexture(this->state.m_textures[i], &(this->m_format), NULL, &(this->m_w), &(this->m_h));
			this->state.m_image_rects.push_back( SDL_Rect{0, 0, m_w, m_h});
		}
	}

	void CAT_AnimationImage::gain(double delta_time) {
		sum_time += delta_time;
	}

	void CAT_AnimationImage::project()
	{
		//sum_time += delta_time;
		double time = fmod(sum_time, this->state.duration_times[state.duration_times.size()-1]);
		int num = 0;

		while(true){
			if(state.duration_times[num] < time){
				num++;
			}else{
				break;
			}
		}

		float draw_w = this->m_w * this->m_transform->get_scale()[0];
		float draw_h = this->m_h * this->m_transform->get_scale()[1];

		// float draw_h = 32;
		// float draw_w = 32;

		Vector3d pos = this->m_transform->get_position();

		this->m_draw_rect = SDL_FRect{(float)pos[0] - draw_w / 2, (float)pos[1] - draw_h / 2, draw_w, draw_h};

		SDL_SetTextureAlphaMod(this->state.m_textures[num], 255);

		SDL_RenderCopyExF(this->m_renderer,
						  this->state.m_textures[num],
						  &(this->state.m_image_rects[num]),
						  &(this->m_draw_rect),
						  0,
						  NULL,
						  SDL_FLIP_NONE);
	}
}