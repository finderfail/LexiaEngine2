#include "../include/Raycaster.h"
#include "../include/Texture.h"  // Добавьте заголовочный файл WallTexture
#include <math.h>
#include <stdlib.h>

Raycaster* Raycaster_create(const Map* map, Screen* screen) {
    Raycaster* raycaster = (Raycaster*)malloc(sizeof(Raycaster));
    if (!raycaster) {
        fprintf(stderr, "Failed to allocate memory for Raycaster\n");
        return NULL;
    }

    raycaster->map = map;
    raycaster->screen = screen;

    return raycaster;
}

void Raycaster_destroy(Raycaster* raycaster) {
    free(raycaster);
}

void Raycaster_castRays(Raycaster* raycaster, const Player* player) {
    if (!raycaster || !player) return;

    const int screenWidth = raycaster->screen->width;
    const int screenHeight = raycaster->screen->height;
    const float fov = M_PI / 3.0f;

    for (int x = 0; x < screenWidth; ++x) {
        float cameraX = 2.0f * x / (float)screenWidth - 1.0f;
        float rayDirX = player->direction.x + cameraX * (-player->direction.y);
        float rayDirY = player->direction.y + cameraX * (player->direction.x);
        float rayAngle = atan2f(rayDirY, rayDirX);

        float distance = Raycaster_getDistanceToWall(raycaster, player->position.x, player->position.y, rayAngle);
        if (distance > 0) {
            int wallHeight = Raycaster_calculateWallHeight(raycaster, distance);
            WallTexture* wallTexture = WallTexture_create(0xFF0000FF);  // Пример цвета (синий)
            Raycaster_drawVerticalLine(raycaster, x, wallHeight, distance, wallTexture);
            WallTexture_destroy(wallTexture);
        }
    }
}

float Raycaster_getDistanceToWall(const Raycaster* raycaster, float playerX, float playerY, float angle) {
    float dirX = cosf(angle);
    float dirY = sinf(angle);

    float mapX = (int)playerX;
    float mapY = (int)playerY;

    float deltaDistX = fabsf(1.0f / dirX);
    float deltaDistY = fabsf(1.0f / dirY);

    float sideDistX = 0.0f;
    float sideDistY = 0.0f;

    int stepX = 0;
    int stepY = 0;

    if (dirX < 0) {
        stepX = -1;
        sideDistX = (playerX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0f - playerX) * deltaDistX;
    }

    if (dirY < 0) {
        stepY = -1;
        sideDistY = (playerY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0f - playerY) * deltaDistY;
    }

    bool hit = false;
    int side = 0;

    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (Map_getTile(raycaster->map, (int)mapX, (int)mapY) != ' ') {
            hit = true;
        }
    }

    if (side == 0) {
        return (mapX - playerX + (1 - stepX) / 2.0f) / dirX;
    } else {
        return (mapY - playerY + (1 - stepY) / 2.0f) / dirY;
    }
}

int Raycaster_calculateWallHeight(const Raycaster* raycaster, float distance) {
    const float cameraPlaneDistance = raycaster->screen->width / (2.0f * tanf(M_PI / 6.0f));
    float wallHeight = cameraPlaneDistance / distance;
    return (int)fminf((float)raycaster->screen->height, wallHeight);
}

void Raycaster_drawVerticalLine(const Raycaster* raycaster, int x, int wallHeight, float distance, const WallTexture* wallTexture) {
    int startY = (raycaster->screen->height - wallHeight) / 2;
    int endY = (raycaster->screen->height + wallHeight) / 2;

    uint32_t color = WallTexture_getColor(wallTexture);

    for (int y = startY; y < endY; ++y) {
        Screen_setPixel(raycaster->screen, x, y, color);
    }
}