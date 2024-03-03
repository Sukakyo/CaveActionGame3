#include "image_storage.h"
#include "debug_log.h"

#include <filesystem>

namespace fs = std::filesystem;

CAT_ImageStorage* CAT_ImageStorage::inst = nullptr;

void CAT_ImageStorage::save_image(const char* file_name){
    fs::path filePath(file_name);
    std::string s_file_name = filePath.filename().string();
    if(this->m_image_map[s_file_name] == nullptr){
        this->m_image_map[s_file_name] = IMG_Load(file_name);
    }else{
        debug::debugLog("Already Save!");
    }
}

SDL_Surface* const CAT_ImageStorage::get_image(const char* file_name){
    fs::path filePath(file_name);
    std::string s_file_name = filePath.filename().string();
    return this->m_image_map[s_file_name];
}