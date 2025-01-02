#include "../include/Config.h"
#include <fstream>
#include <iostream>
#include <sstream>

Config::Config() {}

Config::~Config() {}

bool Config::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file: " << filename << std::endl;
        return false;
    }

    configData_.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            configData_[key] = value;
        }
    }

    file.close();
    return true;
}

std::string Config::get(const std::string& key) const {
    auto it = configData_.find(key);
    if (it != configData_.end()) {
        return it->second;
    }
    return "";
}


int Config::getInt(const std::string& key) const {
    auto it = configData_.find(key);
    if (it != configData_.end()) {
        try {
            return std::stoi(it->second);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid integer value for key '" << key << "'" << std::endl;
            return 0;
        }
        catch(const std::out_of_range& e)
        {
             std::cerr << "Error: Invalid integer value range for key '" << key << "'" << std::endl;
            return 0;
        }
    }
     return 0;
}

void Config::set(const std::string& key, const std::string& value) {
    configData_[key] = value;
}

void Config::setInt(const std::string& key, int value)
{
    configData_[key] = std::to_string(value);
}