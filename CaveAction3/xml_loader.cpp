#include "xml_loader.h"

#include <iostream>

namespace XMLLoader {

	void AnimLoader::Load(const char* xml_file) {

        pugi::xml_document doc;

        pugi::xml_parse_result result = doc.load_string(xml_file);

        for (auto point : doc.child("data").children("animation")) {
            Animation animation;
            for (auto val : point.children("frame")) {
                
                animation.filenames.push_back(std::string(reinterpret_cast<const char*>(val.child_value("filename"))));
                animation.durations.push_back(strtof(reinterpret_cast<const char*>(val.child_value("duration")), nullptr));

                
            }

            this->animations.push_back(animation);
            
        }

	}


}

