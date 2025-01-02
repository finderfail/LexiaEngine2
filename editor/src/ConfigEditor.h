#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include "../src/EditorWindow.h"
#include <string>
#include <unordered_map>
#include <vector>

class ConfigEditor {
public:
    ConfigEditor(EditorWindow& window);
    ~ConfigEditor();
    void run();
    void loadConfig(const std::string& filename);
    void saveConfig(const std::string& filename);
    void handleInput(char input);

private:
  EditorWindow& window_;
  int cursorX_;
  int cursorY_;
    std::unordered_map<std::string, std::string> configData_;
  std::vector<std::string> configKeys_;
  std::string currentInputValue_;
  bool isEditingValue_;
  void drawConfig();
  void addPair(const std::string& key, const std::string& value);
};

#endif