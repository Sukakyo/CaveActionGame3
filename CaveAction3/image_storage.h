#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>

class CAT_ImageStorage{
    private:
    std::map<std::string, SDL_Surface*> m_image_map;

    public:
    void save_image(const char* file_name);
    SDL_Surface* const get_image(const char* file_name);

    // 以下、シングルトン実装 //

    private:
    static CAT_ImageStorage* inst;

    private:
    CAT_ImageStorage() = default;
    ~CAT_ImageStorage() = default;

    public:
    CAT_ImageStorage(const CAT_ImageStorage&) = delete;
    const CAT_ImageStorage& operator=(const CAT_ImageStorage&) = delete;
    CAT_ImageStorage(CAT_ImageStorage&&) = delete;
    const CAT_ImageStorage& operator=(CAT_ImageStorage&&) = delete;

    static CAT_ImageStorage* const getInstance(){
        return inst;
    }

    static void create() {
        if (!inst) {
            inst = new CAT_ImageStorage();
        }
    }

    static void destroy() {
        delete inst;
        inst = nullptr;
    }

};

