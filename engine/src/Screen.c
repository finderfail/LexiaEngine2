#include "../include/Screen.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Screen* Screen_create(int width, int height, const char* title) {
    Screen* screen = (Screen*)malloc(sizeof(Screen));
    if (!screen) {
        fprintf(stderr, "Failed to allocate memory for Screen\n");
        return NULL;
    }

    screen->width = width;
    screen->height = height;
    screen->pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    if (!screen->pixels) {
        fprintf(stderr, "Failed to allocate memory for pixels\n");
        free(screen);
        return NULL;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "LE2 could not initialize! LE_Error: %s\n", SDL_GetError());
        free(screen->pixels);
        free(screen);
        return NULL;
    }

    screen->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!screen->window) {
        fprintf(stderr, "Window could not be created! LE_Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(screen->pixels);
        free(screen);
        return NULL;
    }

    screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
    if (!screen->renderer) {
        fprintf(stderr, "LE2 Renderer could not be created! LE_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(screen->window);
        SDL_Quit();
        free(screen->pixels);
        free(screen);
        return NULL;
    }

    screen->texture = SDL_CreateTexture(screen->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!screen->texture) {
        fprintf(stderr, "LE2 Texture could not be created! LE_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(screen->renderer);
        SDL_DestroyWindow(screen->window);
        SDL_Quit();
        free(screen->pixels);
        free(screen);
        return NULL;
    }

    return screen;
}

void Screen_destroy(Screen* screen) {
    if (screen) {
        if (screen->texture) SDL_DestroyTexture(screen->texture);
        if (screen->renderer) SDL_DestroyRenderer(screen->renderer);
        if (screen->window) SDL_DestroyWindow(screen->window);
        SDL_Quit();
        free(screen->pixels);
        free(screen);
    }
}

void Screen_clear(Screen* screen, uint32_t color) {
    if (screen) {
        memset(screen->pixels, color, screen->width * screen->height * sizeof(uint32_t));
    }
}

void Screen_setPixel(Screen* screen, int x, int y, uint32_t color) {
    if (screen && x >= 0 && x < screen->width && y >= 0 && y < screen->height) {
        screen->pixels[y * screen->width + x] = color;
    }
}

void Screen_render(Screen* screen) {
    if (screen) {
        SDL_UpdateTexture(screen->texture, NULL, screen->pixels, screen->width * sizeof(uint32_t));
        SDL_RenderClear(screen->renderer);
        SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
        SDL_RenderPresent(screen->renderer);
    }
}

void Screen_limitFrameRate(Screen* screen, int fps) {
    static clock_t lastFrameTime = 0;
    clock_t currentTime = clock();
    double frameDuration = (double)(currentTime - lastFrameTime) / CLOCKS_PER_SEC;
    double targetFrameTime = 1.0 / fps;

    if (frameDuration < targetFrameTime) {
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = (targetFrameTime - frameDuration) * 1e9;
        nanosleep(&ts, NULL);
    }

    lastFrameTime = currentTime;
}