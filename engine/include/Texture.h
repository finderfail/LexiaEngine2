#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t color;
    // В будущем можно добавить поддержку текстур
} WallTexture;

WallTexture* WallTexture_create(uint32_t color);
void WallTexture_destroy(WallTexture* wallTexture);
uint32_t WallTexture_getColor(const WallTexture* wallTexture);

#ifdef __cplusplus
}
#endif

#endif // TEXTURE_H