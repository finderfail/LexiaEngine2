#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

typedef struct {
    int width;
    int height;
    char* tiles;
} Map;

Map* Map_create(int width, int height);
void Map_destroy(Map* map);
bool Map_load(Map* map, const char* filename);
char Map_getTile(const Map* map, int x, int y);
bool Map_checkCollision(const Map* map, float x, float y);

#endif // MAP_H