#include "csv_loader.h"


std::vector<std::vector<unsigned short>> CSV_Load(std::string filename) {
    std::ifstream reading_file;
    //std::string filename = "./resource/tilemaps/tilemap1_init.csv";//
    std::vector<std::vector<unsigned short>> tilemap_num;
    
    reading_file.open(filename, std::ios::in);
    std::string reading_line_buffer;

    while(std::getline(reading_file, reading_line_buffer)){
        std::stringstream ss{reading_line_buffer};
        std::string buf;
        std::vector<unsigned short> tilemap_num_line;
        while(std::getline(ss, buf, ',')){
            unsigned short num = std::stoi(buf); 
            tilemap_num_line.push_back(num);
        }
        tilemap_num.push_back(tilemap_num_line);
    }

    return tilemap_num;
}