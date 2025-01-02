#include "MapEditor.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include <termios.h>
#include <unistd.h>

MapEditor::MapEditor(EditorWindow& window) : window_(window), cursorX_(0), cursorY_(0), width_(0), height_(0) {}
MapEditor::~MapEditor(){}

void MapEditor::run() {
    window_.setTitle("Map Editor");
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    while (true) {
      window_.clear();
      drawMap();
      window_.draw();
      char input;
      std::cin >> input;
      handleInput(input);
      if (input == 'q') break;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
}
void MapEditor::loadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open map file: " << filename << std::endl;
        return;
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
                    return;
                }
        }
    } else {
      std::cerr << "Error: Map file is empty" << std::endl;
       width_ = 16;
       height_ = 16;
       mapData_.resize(height_, std::string(width_,' '));
    }
    
    file.close();
}
void MapEditor::saveMap(const std::string& filename) {
  std::ofstream file(filename);
  if (file.is_open())
  {
     for(const auto& line : mapData_)
      file << line << std::endl;
     file.close();
  } else {
    std::cerr << "Error: Could not save map file: " << filename << std::endl;
  }
}

void MapEditor::handleInput(char input) {
   switch (input) {
        case 'w':
            if(cursorY_ > 0) cursorY_--;
            break;
        case 's':
            if (cursorY_ < height_ - 1) cursorY_++;
            break;
        case 'a':
             if(cursorX_ > 0) cursorX_--;
            break;
        case 'd':
            if (cursorX_ < width_ - 1) cursorX_++;
            break;
        case 'e':
            mapData_[cursorY_][cursorX_] = '#';
            break;
        case 'r':
            mapData_[cursorY_][cursorX_] = ' ';
            break;
   }
}

void MapEditor::drawMap() {
  int offsetX = (window_.getWidth() - width_)/2;
  int offsetY = (window_.getHeight() - height_)/2;
   for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
          if(x == cursorX_ && y == cursorY_)
          {
              window_.setPixel(offsetX + x, offsetY + y, '[');
              window_.setPixel(offsetX + x + 1, offsetY + y, ']');
              x++;
              continue;
          }
          
          window_.setPixel(offsetX + x, offsetY + y, mapData_[y][x]);
        }
    }
}