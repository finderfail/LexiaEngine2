#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <cstdint>
#include <string>
#include <SDL.h>

class Screen {
public:
    Screen(int width, int height, const char* title);
    ~Screen();

    int getWidth() const;
    int getHeight() const;

    void clear(uint32_t color = 0);
    void setPixel(int x, int y, uint32_t color);
    void limitFrameRate(int fps);
    void render();

private:
    int width_;
    int height_;
    std::vector<uint32_t> pixels_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Texture* texture_;
};

#endif