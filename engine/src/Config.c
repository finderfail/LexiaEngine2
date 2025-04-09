#include "../include/Config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_CAPACITY 10

Config* Config_create() {
    Config* config = (Config*)malloc(sizeof(Config));
    if (!config) {
        fprintf(stderr, "Failed to allocate memory for Config\n");
        return NULL;
    }

    config->entries = (ConfigEntry*)malloc(INITIAL_CAPACITY * sizeof(ConfigEntry));
    if (!config->entries) {
        fprintf(stderr, "Failed to allocate memory for Config entries\n");
        free(config);
        return NULL;
    }

    config->size = 0;
    config->capacity = INITIAL_CAPACITY;

    return config;
}

void Config_destroy(Config* config) {
    if (config) {
        free(config->entries);
        free(config);
    }
}

bool Config_load(Config* config, const char* filename) {
    if (!config) return false;

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open config file: %s\n", filename);
        return false;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char key[256];
        char value[256];
        if (sscanf(line, "%255[^=]=%255[^\n]", key, value) == 2) {
            Config_set(config, key, value);
        }
    }

    fclose(file);
    return true;
}

const char* Config_get(const Config* config, const char* key) {
    if (!config) return NULL;

    for (int i = 0; i < config->size; ++i) {
        if (strcmp(config->entries[i].key, key) == 0) {
            return config->entries[i].value;
        }
    }

    return NULL;
}

int Config_getInt(const Config* config, const char* key) {
    const char* value = Config_get(config, key);
    if (value) {
        return atoi(value);
    }
    return 0;
}

void Config_set(Config* config, const char* key, const char* value) {
    if (!config) return;

    for (int i = 0; i < config->size; ++i) {
        if (strcmp(config->entries[i].key, key) == 0) {
            strncpy(config->entries[i].value, value, sizeof(config->entries[i].value) - 1);
            config->entries[i].value[sizeof(config->entries[i].value) - 1] = '\0';
            return;
        }
    }

    if (config->size == config->capacity) {
        config->capacity *= 2;
        config->entries = (ConfigEntry*)realloc(config->entries, config->capacity * sizeof(ConfigEntry));
        if (!config->entries) {
            fprintf(stderr, "Failed to reallocate memory for Config entries\n");
            return;
        }
    }

    strncpy(config->entries[config->size].key, key, sizeof(config->entries[config->size].key) - 1);
    config->entries[config->size].key[sizeof(config->entries[config->size].key) - 1] = '\0';
    strncpy(config->entries[config->size].value, value, sizeof(config->entries[config->size].value) - 1);
    config->entries[config->size].value[sizeof(config->entries[config->size].value) - 1] = '\0';
    config->size++;
}

void Config_setInt(Config* config, const char* key, int value) {
    char strValue[256];
    snprintf(strValue, sizeof(strValue), "%d", value);
    Config_set(config, key, strValue);
}