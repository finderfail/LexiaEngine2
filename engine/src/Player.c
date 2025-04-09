#include "../include/Player.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Player* Player_create(float x, float y, float direction) {
    Player* player = (Player*)malloc(sizeof(Player));
    if (!player) {
        fprintf(stderr, "Failed to allocate memory for Player\n");
        return NULL;
    }

    player->position.x = x;
    player->position.y = y;
    player->direction.x = cosf(direction);
    player->direction.y = sinf(direction);

    return player;
}

void Player_destroy(Player* player) {
    free(player);
}

void Player_move(Player* player, float distance, const Map* map) {
    if (!player) return;

    float oldX = player->position.x;
    float oldY = player->position.y;

    float newX = player->position.x + player->direction.x * distance;
    float newY = player->position.y + player->direction.y * distance;

    if (!Map_checkCollision(map, newX, newY)) {
        player->position.x = newX;
        player->position.y = newY;
    } else {
        newX = player->position.x + player->direction.x * distance;
        if (!Map_checkCollision(map, newX, player->position.y)) {
            player->position.x = newX;
        }

        newY = player->position.y + player->direction.y * distance;
        if (!Map_checkCollision(map, player->position.x, newY)) {
            player->position.y = newY;
        }
    }
}

void Player_rotate(Player* player, float angle) {
    if (!player) return;

    float oldDirX = player->direction.x;
    player->direction.x = player->direction.x * cosf(angle) - player->direction.y * sinf(angle);
    player->direction.y = oldDirX * sinf(angle) + player->direction.y * cosf(angle);
}

Point2D Player_getPosition(const Player* player) {
    return player->position;
}

Vector2D Player_getDirection(const Player* player) {
    return player->direction;
}