#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"

typedef struct {
    float x;
    float y;
} Point2D;

typedef struct {
    float x;
    float y;
} Vector2D;

typedef struct {
    Point2D position;
    Vector2D direction;
} Player;

Player* Player_create(float x, float y, float direction);
void Player_destroy(Player* player);
void Player_move(Player* player, float distance, const Map* map);
void Player_rotate(Player* player, float angle);
Point2D Player_getPosition(const Player* player);
Vector2D Player_getDirection(const Player* player);

#endif // PLAYER_H