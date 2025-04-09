# Lexia Engine Documentation

## Overview

Lexia Engine is a simple game engine written in C. It provides basic functionality for creating 2.5D (3D like DOOM) games, including rendering, input handling, and configuration management.

## Components

### 1. Screen

The `Screen` component is responsible for rendering the game window and handling pixel operations.

#### Functions

- `Screen* Screen_create(int width, int height, const char* title)`
  - Creates a new screen with the specified width, height, and title.
  - Returns a pointer to the created `Screen` object.

- `void Screen_destroy(Screen* screen)`
  - Destroys the specified screen and frees associated resources.

- `void Screen_clear(Screen* screen, uint32_t color)`
  - Clears the screen with the specified color.

- `void Screen_setPixel(Screen* screen, int x, int y, uint32_t color)`
  - Sets the pixel at the specified coordinates to the specified color.

- `void Screen_render(Screen* screen)`
  - Renders the screen.

- `void Screen_limitFrameRate(Screen* screen, int fps)`
  - Limits the frame rate to the specified FPS.

### 2. Map

The `Map` component is responsible for loading and managing the game map.

#### Functions

- `Map* Map_create(int width, int height)`
  - Creates a new map with the specified width and height.
  - Returns a pointer to the created `Map` object.

- `void Map_destroy(Map* map)`
  - Destroys the specified map and frees associated resources.

- `bool Map_load(Map* map, const char* filename)`
  - Loads the map from the specified file.
  - Returns `true` if the map was loaded successfully, `false` otherwise.

- `char Map_getTile(const Map* map, int x, int y)`
  - Returns the tile at the specified coordinates.

- `bool Map_checkCollision(const Map* map, float x, float y)`
  - Checks for collisions at the specified coordinates.
  - Returns `true` if a collision is detected, `false` otherwise.

### 3. Player

The `Player` component is responsible for managing the player's position and direction.

#### Functions

- `Player* Player_create(float x, float y, float direction)`
  - Creates a new player at the specified coordinates with the specified direction.
  - Returns a pointer to the created `Player` object.

- `void Player_destroy(Player* player)`
  - Destroys the specified player and frees associated resources.

- `void Player_move(Player* player, float distance, const Map* map)`
  - Moves the player by the specified distance, taking into account collisions with the map.

- `void Player_rotate(Player* player, float angle)`
  - Rotates the player by the specified angle.

- `Point2D Player_getPosition(const Player* player)`
  - Returns the player's current position.

- `Vector2D Player_getDirection(const Player* player)`
  - Returns the player's current direction.

### 4. Raycaster

The `Raycaster` component is responsible for casting rays and rendering the 3D view.

#### Functions

- `Raycaster* Raycaster_create(const Map* map, Screen* screen)`
  - Creates a new raycaster with the specified map and screen.
  - Returns a pointer to the created `Raycaster` object.

- `void Raycaster_destroy(Raycaster* raycaster)`
  - Destroys the specified raycaster and frees associated resources.

- `void Raycaster_castRays(Raycaster* raycaster, const Player* player)`
  - Casts rays from the player's position and renders the 3D view.

- `float Raycaster_getDistanceToWall(const Raycaster* raycaster, float playerX, float playerY, float angle)`
  - Returns the distance to the nearest wall in the specified direction.

- `int Raycaster_calculateWallHeight(const Raycaster* raycaster, float distance)`
  - Calculates the height of the wall at the specified distance.

- `void Raycaster_drawVerticalLine(const Raycaster* raycaster, int x, int wallHeight, float distance)`
  - Draws a vertical line representing a wall at the specified coordinates.

### 5. Config

The `Config` component is responsible for loading and managing configuration settings.

#### Functions

- `Config* Config_create()`
  - Creates a new configuration object.
  - Returns a pointer to the created `Config` object.

- `void Config_destroy(Config* config)`
  - Destroys the specified configuration object and frees associated resources.

- `bool Config_load(Config* config, const char* filename)`
  - Loads the configuration from the specified file.
  - Returns `true` if the configuration was loaded successfully, `false` otherwise.

- `const char* Config_get(const Config* config, const char* key)`
  - Returns the value associated with the specified key.

- `int Config_getInt(const Config* config, const char* key)`
  - Returns the integer value associated with the specified key.

- `void Config_set(Config* config, const char* key, const char* value)`
  - Sets the value associated with the specified key.

- `void Config_setInt(Config* config, const char* key, int value)`
  - Sets the integer value associated with the specified key.
