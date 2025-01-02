#include "EditorWindow.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>

EditorWindow::EditorWindow(int width, int height, const std::string& title)
    : width_(width), height_(height), title_(title) {
  buffer_ = new char[width_ * height_];
  std::memset(buffer_, ' ', width_*height_);
  
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  if (width_ > size.ws_col || height_ > size.ws_row)
  {
      std::cerr << "Error: terminal size is too small! (needed: 120x30)" << std::endl;
      exit(1);
  }
}

EditorWindow::~EditorWindow() {
    delete[] buffer_;
}

void EditorWindow::clear() {
  std::memset(buffer_, ' ', width_*height_);
}

void EditorWindow::draw() {
    std::cout << "\033[H";  
  
    std::cout << title_ << std::endl;

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
           std::cout << buffer_[y * width_ + x];
        }
      std::cout << std::endl;
    }
}
void EditorWindow::setTitle(const std::string& title){
    title_ = title;
}
void EditorWindow::setPixel(int x, int y, char c) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        buffer_[y * width_ + x] = c;
    }
}
int EditorWindow::getWidth() const {
  return width_;
}
int EditorWindow::getHeight() const {
  return height_;
}