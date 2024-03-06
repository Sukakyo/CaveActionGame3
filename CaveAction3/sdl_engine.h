#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>


#include <eigen3/Eigen/Core>
#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_PARALLELIZE
#define EIGEN_MPL2_ONLY


#include "debug_log.h"
#include "image_storage.h"
#include "image_projecter.h"
#include "collider_manager.h"

#include "game_object.h"
#include "field.h"

#include "image.h"
#include "rigidbody.h"
#include "virtual_controller.h"

using namespace component;

class CAT_SDLEngine {
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_GameController* m_controller = nullptr;
    ImageProjecter* m_projecter;
    ColliderManager* m_collider_manager;

    int count = 0;
	int quit = 0;
	SDL_Event e;

    enum TypeController {
        KEY_MOUSE,
        PAD_CONTROLLER
    };

    TypeController type_controller = PAD_CONTROLLER;

    struct CAT_Input{

        Eigen::Vector2i direction = Vector2i(0,1);
        double sum_time = 0;
        
	    int right = 0;
	    int left = 0;
	    int front = 0;
	    int back = 0;
	
	    int escape = 0;

        int type = 0;
    };

    CAT_Input input;

    Uint32 frameStart, frameTime;
    Uint32 preDeltaTime = 0;


    Field* field;

    GameObject* gb1;

    GameObject* gb2;

private:

    void AddController(int index);
    void RemoveController();


public:
    int InitEngine();
    int InitObject();
    int Update();
    int Draw();
    int Finish();

    int Judge();
};