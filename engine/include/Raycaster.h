#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "Map.h"
#include "Screen.h"
#include "Player.h"
#include "Texture.h" 

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const Map* map;
    Screen* screen;
} Raycaster;

Raycaster* Raycaster_create(const Map* map, Screen* screen);
void Raycaster_destroy(Raycaster* raycaster);
void Raycaster_castRays(Raycaster* raycaster, const Player* player);
float Raycaster_getDistanceToWall(const Raycaster* raycaster, float playerX, float playerY, float angle);
int Raycaster_calculateWallHeight(const Raycaster* raycaster, float distance);
void Raycaster_drawVerticalLine(const Raycaster* raycaster, int x, int wallHeight, float distance, const WallTexture* wallTexture);

#ifdef __cplusplus
}
#endif

#endif // RAYCASTER_H