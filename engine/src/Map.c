#include "../include/Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Map* Map_create(int width, int height) {
    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) {
        fprintf(stderr, "Failed to allocate memory for Map\n");
        return NULL;
    }

    map->width = width;
    map->height = height;
    map->tiles = (char*)malloc(width * height * sizeof(char));
    if (!map->tiles) {
        fprintf(stderr, "Failed to allocate memory for map tiles\n");
        free(map);
        return NULL;
    }

    memset(map->tiles, ' ', width * height);

    return map;
}

void Map_destroy(Map* map) {
    if (map) {
        free(map->tiles);
        free(map);
    }
}

bool Map_load(Map* map, const char* filename) {
    if (!map) return false;

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open map file: %s\n", filename);
        return false;
    }

    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            int c = fgetc(file);
            if (c == EOF) {
                fclose(file);
                return false;
            }
            map->tiles[y * map->width + x] = (char)c;
        }
        fgetc(file); // Skip newline character
    }

    fclose(file);
    return true;
}

char Map_getTile(const Map* map, int x, int y) {
    if (!map || x < 0 || x >= map->width || y < 0 || y >= map->height) {
        return ' ';
    }
    return map->tiles[y * map->width + x];
}

bool Map_checkCollision(const Map* map, float x, float y) {
    int mapX = (int)x;
    int mapY = (int)y;

    if (mapX < 0 || mapX >= map->width || mapY < 0 || mapY >= map->height || Map_getTile(map, mapX, mapY) != ' ') {
        return true;
    }

    return false;
}