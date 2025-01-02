#include "ConfigEditor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

ConfigEditor::ConfigEditor(EditorWindow& window) : window_(window), cursorX_(0), cursorY_(0), isEditingValue_(false) {}

ConfigEditor::~ConfigEditor() {}

void ConfigEditor::run() {
    window_.setTitle("Lexia Development Kit: Config Editor");
    while (true) {
      window_.clear();
      drawConfig();
      window_.draw();
      char input;
      std::cin >> input;
      handleInput(input);
      if (input == 'q') break;
    }
}
void ConfigEditor::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file: " << filename << std::endl;
        return;
    }

    configData_.clear();
    configKeys_.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
          configData_[key] = value;
          configKeys_.push_back(key);
        }
    }

    file.close();
}
void ConfigEditor::saveConfig(const std::string& filename) {
  std::ofstream file(filename);
  if (file.is_open())
  {
    for (const auto& key : configKeys_)
    {
      file << key << "=" << configData_[key] << std::endl;
    }
     file.close();
  } else {
    std::cerr << "Error: Could not save config file: " << filename << std::endl;
  }
}

void ConfigEditor::handleInput(char input) {
      if (isEditingValue_)
      {
          if (input == '\n')
              isEditingValue_ = false;
          else if(input == '\b')
          {
              if (!currentInputValue_.empty())
                  currentInputValue_.pop_back();
          }
          else
            currentInputValue_ += input;
      }
        else
        {
           switch (input) {
                case 'w':
                  if(cursorY_ > 0) cursorY_--;
                    break;
                case 's':
                    if (cursorY_ < configKeys_.size()) cursorY_++;
                    break;
                case 'e':
                     if (cursorY_ < configKeys_.size())
                        {
                            currentInputValue_ = configData_[configKeys_[cursorY_]];
                            isEditingValue_ = true;
                        }
                    break;
                case 'a':
                    addPair("new_key","new_value");
                     break;
           }
      }
  if (!isEditingValue_ && !configKeys_.empty() && cursorY_ < configKeys_.size())
      configData_[configKeys_[cursorY_]] = currentInputValue_;
}
void ConfigEditor::addPair(const std::string& key, const std::string& value)
{
  configData_[key] = value;
  configKeys_.push_back(key);
}
void ConfigEditor::drawConfig() {
  int offsetX = 5;
  int offsetY = 5;

  for (size_t i = 0; i < configKeys_.size(); i++) {
        std::string key = configKeys_[i];
        std::string value = configData_[key];
       if(i == cursorY_)
        {
          window_.setPixel(offsetX, offsetY + i, '[');
          window_.setPixel(offsetX + key.size() + 1 + value.size() + 2, offsetY + i, ']');
        }
        for (size_t x = 0; x < key.size(); x++)
            window_.setPixel(offsetX + x + 1, offsetY + i, key[x]);
        window_.setPixel(offsetX + key.size() + 1, offsetY + i, '=');
        for(size_t x = 0; x < value.size(); x++)
            window_.setPixel(offsetX + key.size() + 2 + x, offsetY + i, value[x]);
    }
     if(isEditingValue_ && !configKeys_.empty() && cursorY_ < configKeys_.size())
     {
           std::string key = configKeys_[cursorY_];
           window_.setPixel(offsetX + key.size() + 2 + configData_[key].size(), offsetY + cursorY_, '[');
            window_.setPixel(offsetX + key.size() + 2 + configData_[key].size() + currentInputValue_.size() + 1, offsetY + cursorY_, ']');
            for(size_t x = 0; x < currentInputValue_.size(); x++)
                window_.setPixel(offsetX + key.size() + 2 + configData_[key].size() + 1 + x, offsetY + cursorY_, currentInputValue_[x]);

     }
}