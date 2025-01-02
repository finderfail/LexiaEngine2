#include "../include/Map.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() : width_(0), height_(0) {}

Map::~Map() {}

bool Map::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open map file: " << filename << std::endl;
        return false;
    }

    mapData_.clear();
    std::string line;
    while (std::getline(file, line)) {
        mapData_.push_back(line);
    }

    if (!mapData_.empty()) {
        height_ = mapData_.size();
        width_ = mapData_[0].size();
        for (const auto& row : mapData_)
        {
            if (row.size() != width_)
                {
                    std::cerr << "Error: inconsistent map width!" << std::endl;
                    return false;
                }
        }
    } else {
        std::cerr << "Error: Map file is empty" << std::endl;
        return false;
    }
    
    
    file.close();
    return true;
}

char Map::getTile(int x, int y) const {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        return mapData_[y][x];
    }
    return ' ';
}

int Map::getWidth() const {
    return width_;
}

int Map::getHeight() const {
    return height_;
}