#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "../src/EditorWindow.h"
#include <string>
#include <vector>

class MapEditor {
public:
    MapEditor(EditorWindow& window);
    ~MapEditor();
    void run();
    void loadMap(const std::string& filename);
    void saveMap(const std::string& filename);
    void handleInput(char input);
private:
  EditorWindow& window_;
  int cursorX_;
  int cursorY_;
  std::vector<std::string> mapData_;
    int width_;
    int height_;
    void drawMap();
};
#endif