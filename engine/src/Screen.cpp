#include "../include/Screen.h"
#include <iostream>
#include <vector>

Screen::Screen(int width, int height) : width_(width), height_(height) {
  buffer_.resize(width_ * height_, ' ');
}

Screen::~Screen() {}

void Screen::clear() {
  for (char& pixel : buffer_) {
    pixel = ' ';
  }
}

void Screen::draw() {
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      std::cout << buffer_[y * width_ + x];
    }
    std::cout << std::endl;
  }
}

void Screen::setPixel(int x, int y, char c) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        buffer_[y * width_ + x] = c;
    }
}

int Screen::getWidth() const {
  return width_;
}

int Screen::getHeight() const {
  return height_;
}