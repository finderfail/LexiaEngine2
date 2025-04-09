#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
    char key[256];
    char value[256];
} ConfigEntry;

typedef struct {
    ConfigEntry* entries;
    int size;
    int capacity;
} Config;

Config* Config_create();
void Config_destroy(Config* config);
bool Config_load(Config* config, const char* filename);
const char* Config_get(const Config* config, const char* key);
int Config_getInt(const Config* config, const char* key);
void Config_set(Config* config, const char* key, const char* value);
void Config_setInt(Config* config, const char* key, int value);

#endif // CONFIG_H