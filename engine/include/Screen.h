#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <stdint.h>

typedef struct {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t* pixels;
} Screen;

Screen* Screen_create(int width, int height, const char* title);
void Screen_destroy(Screen* screen);
void Screen_clear(Screen* screen, uint32_t color);
void Screen_setPixel(Screen* screen, int x, int y, uint32_t color);
void Screen_render(Screen* screen);
void Screen_limitFrameRate(Screen* screen, int fps);

#endif // SCREEN_H