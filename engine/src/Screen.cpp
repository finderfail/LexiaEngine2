#include "../include/Screen.h"
#include <SDL.h>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

Screen::Screen(int width, int height, const char* title) : width_(width), height_(height), pixels_(width * height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "LE2 could not initialize! LE_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Lexia Engine 2 init failed");
    }

    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
    if (window_ == nullptr)
    {
        std::cerr << "Window could not be created! LE_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("Lexia Engine 2: Window creation failed");
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr)
    {
        std::cerr << "LE2 Renderer could not be created! LE_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("Lexia Engine 2: Renderer creation failed");
    }

    texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width_, height_);
    if(texture_ == nullptr)
    {
        std::cerr << "LE2 Texture could not be created! LE_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error("Lexia Engine 2: Texture creation failed");
    }
}

Screen::~Screen() {
    if (texture_ != nullptr) SDL_DestroyTexture(texture_);
    if (renderer_ != nullptr) SDL_DestroyRenderer(renderer_);
    if(window_ != nullptr) SDL_DestroyWindow(window_);
    SDL_Quit();
}

int Screen::getWidth() const {
    return width_;
}

int Screen::getHeight() const {
    return height_;
}

void Screen::clear(uint32_t color) {
    std::fill(pixels_.begin(), pixels_.end(), color);
}

void Screen::setPixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        pixels_[y * width_ + x] = color;
    }
}

void Screen::render() {
    SDL_UpdateTexture(texture_, nullptr, pixels_.data(), width_ * sizeof(uint32_t));
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);
}

void Screen::limitFrameRate(int fps) {
    static auto lastFrameTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> frameDuration = currentTime - lastFrameTime;
    float frameTime = frameDuration.count();

    float targetFrameTime = 1.0f / fps;
    if (frameTime < targetFrameTime) {
        std::this_thread::sleep_for(std::chrono::duration<float>(targetFrameTime - frameTime));
    }

    lastFrameTime = std::chrono::high_resolution_clock::now();
}