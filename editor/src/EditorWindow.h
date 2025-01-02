#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H
#include <string>
class EditorWindow {
public:
    EditorWindow(int width, int height, const std::string& title);
    ~EditorWindow();
    void clear();
    void draw();
    void setTitle(const std::string& title);
    void setPixel(int x, int y, char c);
    int getWidth() const;
    int getHeight() const;
private:
    int width_;
    int height_;
    std::string title_;
    char* buffer_;
};
#endif