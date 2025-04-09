#include "../include/Raycaster.h"
#include <cmath>
#include <iostream>
#include <algorithm>

Raycaster::Raycaster(const Map& map, Screen& screen) : map_(map), screen_(screen) {}

void Raycaster::castRays(const Player& player) {
    const int screenWidth = screen_.getWidth();
    const int screenHeight = screen_.getHeight();
    const float fov = M_PI / 3.0f;

    for (int x = 0; x < screenWidth; ++x) {
        float cameraX = 2.0f * x / static_cast<float>(screenWidth) - 1.0f;
        float rayDirX = player.getDirection().x + cameraX * (-player.getDirection().y);
        float rayDirY = player.getDirection().y + cameraX * (player.getDirection().x);
        float rayAngle = std::atan2(rayDirY, rayDirX);

        float distance = getDistanceToWall(player.getPosition().x, player.getPosition().y, rayAngle);
        if (distance > 0)
        {
            int wallHeight = calculateWallHeight(distance);
            drawVerticalLine(x, wallHeight, distance);
        }
    }

    // Limit the frame rate to 120 FPS
    screen_.limitFrameRate(120);
}

float Raycaster::getDistanceToWall(float playerX, float playerY, float angle) const {
    float dirX = std::cos(angle);
    float dirY = std::sin(angle);

    float mapX = static_cast<int>(playerX);
    float mapY = static_cast<int>(playerY);

    float deltaDistX = std::abs(1.0f / dirX);
    float deltaDistY = std::abs(1.0f / dirY);

    float sideDistX = 0.0;
    float sideDistY = 0.0;

    int stepX = 0;
    int stepY = 0;

    if (dirX < 0)
    {
        stepX = -1;
        sideDistX = (playerX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0f - playerX) * deltaDistX;
    }

    if (dirY < 0)
    {
        stepY = -1;
        sideDistY = (playerY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0f - playerY) * deltaDistY;
    }

    bool hit = false;
    int side = 0;

    while(!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (map_.getTile(mapX, mapY) != ' ')
            hit = true;
    }

    if (side == 0)
        return (mapX - playerX + (1 - stepX) / 2.0) / dirX;
    else
        return (mapY - playerY + (1 - stepY) / 2.0) / dirY;
}

float Raycaster::calculateWallHeight(float distance) const {
    const float cameraPlaneDistance = screen_.getWidth() / (2.0f * std::tan(M_PI / 6.0f));
    float wallHeight = cameraPlaneDistance / distance;
    return std::min(static_cast<float>(screen_.getHeight()), wallHeight);
}

void Raycaster::drawVerticalLine(int x, int wallHeight, float distance) const {
    int startY = (screen_.getHeight() - wallHeight) / 2;
    int endY = (screen_.getHeight() + wallHeight) / 2;

    for (int y = startY; y < endY; ++y) {
        float brightness = 1.0f - std::min(1.0f, distance / 10.0f);
        char pixelChar = '#';

        if (brightness < 0.2)
            pixelChar = '.'; // most far wall
        else if(brightness < 0.4)
            pixelChar = ','; // far wall
        else if(brightness < 0.6)
            pixelChar = '-'; // mid wall
        else if (brightness < 0.8)
            pixelChar = '='; // near wall
        screen_.setPixel(x, y, pixelChar);
    }
}