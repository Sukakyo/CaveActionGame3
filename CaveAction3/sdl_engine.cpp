#include "sdl_engine.h"


#define SCREEN_WIDTH (640)
#define SCREEN_HEIGHT (480)


#include <pugixml.hpp>
#include <iostream>



int CAT_SDLEngine::InitEngine()
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        debug::debugLog("Error: Failed to initialize SDL!\n");
        return -1;
    }

    m_window = SDL_CreateWindow(
        "SDL_Image_test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_BORDERLESS);

    if (m_window == nullptr)
    {
        debug::debugLog("Error: Failed to initialize window!\n");
        return -1;
    }

    m_renderer = SDL_CreateRenderer(m_window,
                                    -1,
                                    SDL_RENDERER_SOFTWARE);

    if (m_renderer == nullptr)
    {
        
        debug::debugLog("Error: Failed to initialize renderer!");
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return -1;
    }


    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);



    for (auto i = 0, joystick_count = SDL_NumJoysticks(); i < joystick_count; i++)
    {
        if (!SDL_IsGameController(i)) continue;

        this->AddController(i);
    }



    CAT_ImageStorage::create();

    m_projecter = new ImageProjecter();

    return 0;
}

int CAT_SDLEngine::InitObject()
{
    field = new Field("Field1", Vector3d(160, 80, 0), m_renderer, m_projecter);
    field->set_scale(Vector3d(1.0,1.0,1.0));

    gb1 = new GameObject("ObjectA", Vector3d(320, 240, 0), m_renderer, m_projecter);
    gb1->set_scale(Vector3d(1.0, 1.0, 1.0));

    gb2 = new GameObject("ObjectX", Vector3d(400, 240, 0), m_renderer, m_projecter);
    gb2->set_scale(Vector3d(1.0, 1.0, 1.0));

    


    return 0;
}


int CAT_SDLEngine::Update()
{
    frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = 1;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (this->type_controller == CAT_SDLEngine::KEY_MOUSE) {

                if (e.key.keysym.sym == SDLK_d)
                {
                    input.right = 1;
                }


                if (e.key.keysym.sym == SDLK_a)
                {
                    input.left = 1;
                }


                if (e.key.keysym.sym == SDLK_w)
                {
                    input.front = 1;
                }

                if (e.key.keysym.sym == SDLK_s)
                {
                    input.back = 1;
                }

                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    input.escape = 1;
                }

            }

        }
        else if (e.type == SDL_KEYUP)
        {
            if (this->type_controller == CAT_SDLEngine::KEY_MOUSE) {

                if (e.key.keysym.sym == SDLK_d)
                {
                    input.right = 0;
                }


                if (e.key.keysym.sym == SDLK_a)
                {
                    input.left = 0;
                }


                if (e.key.keysym.sym == SDLK_w)
                {
                    input.front = 0;
                }


                if (e.key.keysym.sym == SDLK_s)
                {
                    input.back = 0;
                }

                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    input.escape = 0;
                }

            }

            

        }
        else if (e.type == SDL_CONTROLLERDEVICEADDED) {
            AddController(e.cdevice.which);
            if (m_controller == nullptr) quit = 1;
        }
        else if (e.type == SDL_CONTROLLERDEVICEREMOVED) {
            RemoveController();
        }
    }

    if (this->type_controller == CAT_SDLEngine::PAD_CONTROLLER) {
        if (SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_UP) > 0) {
            input.front = 1;
        }
        else {
            input.front = 0;
        }

        if (SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) > 0) {
            input.left = 1;
        }
        else {
            input.left = 0;
        }

        if (SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) > 0) {
            input.right = 1;
        }
        else {
            input.right = 0;
        }

        if (SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) > 0) {
            input.back = 1;
        }
        else {
            input.back = 0;
        }

        if (SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_START) > 0) {
            input.escape = 1;
        }
        else {
            input.escape = 0;
        }
    
    }


    SDL_RenderClear(m_renderer);

    int vertical = -(input.front - input.back);
    int horizontal = input.right - input.left;

    if (vertical == 1) {
        gb1->change_anim(0);
    }
    else if (vertical == -1) {
        gb1->change_anim(3);
    }
    else if (horizontal == 1) {
        gb1->change_anim(2);
    }
    else if (horizontal == -1) {
        gb1->change_anim(1);
    }

    gb1->input(Vector3d(horizontal, vertical, 0).normalized());
    
    gb1->get_box_collider_2d()->update();
    gb2->get_box_collider_2d()->update();
    if(gb1->get_box_collider_2d()->judge(gb2->get_box_collider_2d()) > 0){
        
    }

    if(gb2->get_box_collider_2d()->judge(gb1->get_box_collider_2d()) > 0){
         
    }
    field->get_tilecollider()->judge(gb1->get_box_collider_2d());
    field->get_tilecollider()->judge(gb2->get_box_collider_2d());

    field->project();
    gb1->project();
    gb2->project();
    this->m_projecter->project();
    
    SDL_RenderPresent(m_renderer);

    count++;

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < 15)
    {
        SDL_Delay(15 - frameTime);
        frameTime = SDL_GetTicks() - frameStart;
    }

    preDeltaTime = frameTime;

    gb1->gain(frameTime);
    gb2->gain(frameTime);

    debug::debugLog("%d\n", frameTime);

    return 0;
}

int CAT_SDLEngine::Finish(){
    if(!quit){
		SDL_Delay(5000);
	}

    delete field;

    delete gb1;
    delete gb2;

	CAT_ImageStorage::destroy();
    delete m_projecter;

    this->RemoveController();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();


    return 0;


}

int CAT_SDLEngine::Judge(){
    return (count > 5000) || (input.escape > 0) || (quit > 0);
}


void CAT_SDLEngine::AddController(int index) {
    if (m_controller != nullptr) return;
    m_controller = SDL_GameControllerOpen(index);
    debug::debugLog("Open Game Controller!\n");

    if (m_controller != nullptr) return;
    debug::debugLog("Error : Failed to Open Game Controller!\n");
}

void CAT_SDLEngine::RemoveController() {
    if (m_controller == nullptr) return;

    SDL_GameControllerClose(m_controller);
    m_controller = nullptr;
}