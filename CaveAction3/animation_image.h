#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include "transform.h"

#include <vector>

#include "raw_image.h"

namespace component
{

	class CAT_AnimationImage : public CAT_RawImage
	{
	private:
		struct State{
			std::vector<SDL_Surface*> m_images;
			std::vector<SDL_Texture*> m_textures;
			std::vector<SDL_Rect> m_image_rects;
			//std::vector<int> m_w;//
			//std::vector<int> m_h;//

			std::vector<double> duration_times;
		};

		//SDL_Surface *m_image; // 画像 //
		int m_w;			  // 幅 //
		int m_h;			  // 高さ //
		SDL_Renderer *m_renderer;
		//SDL_Texture *m_texture; //
		//SDL_Rect m_image_rect; //
		SDL_FRect m_draw_rect;
		Uint32 m_format;
		
		double sum_time = 0;

		State state;

	public:
		CAT_AnimationImage(CAT_Transform *const transform, std::vector<const char *>path, std::vector<double> durations, SDL_Renderer *const renderer);
		void gain(double delta_time);
		void project() override;
	};
}
