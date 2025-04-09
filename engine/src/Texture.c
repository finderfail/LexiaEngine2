#include "../include/Texture.h"
#include <stdlib.h>
#include <stdio.h>

WallTexture* WallTexture_create(uint32_t color) {
    WallTexture* wallTexture = (WallTexture*)malloc(sizeof(WallTexture));
    if (!wallTexture) {
        fprintf(stderr, "Failed to allocate memory for WallTexture\n");
        return NULL;
    }

    wallTexture->color = color;
    return wallTexture;
}

void WallTexture_destroy(WallTexture* wallTexture) {
    free(wallTexture);
}

uint32_t WallTexture_getColor(const WallTexture* wallTexture) {
    return wallTexture->color;
}