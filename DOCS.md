# Lexia Engine Documentation

## Overview

Lexia Engine is a versatile game engine written in C. It provides a robust foundation for creating 2.5D (Doom like) games, with features including rendering, input handling, and configuration management. This documentation is intended for developers and enthusiasts who wish to understand the inner workings of the engine and leverage its capabilities to create their own games.

## Dependencies

Lexia Engine uses the following external libraries:

- **SDL2**: Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It is used for window management and rendering.

To install SDL2, you can use the following commands:

- **macOS**: `brew install sdl2`
- **Ubuntu**: `sudo apt-get install libsdl2-dev`
- **Windows**: Download the development libraries from the [SDL website](https://www.libsdl.org/download-2.0.php) and follow the installation instructions.

## Components

### 1. Screen

The `Screen` component is responsible for rendering the game window and handling pixel operations. It uses SDL2 for window management and rendering.

#### Functions

- `Screen* Screen_create(int width, int height, const char* title)`
  - **Description**: Creates a new screen with the specified width, height, and title.
  - **Parameters**:
    - `width`: The width of the screen.
    - `height`: The height of the screen.
    - `title`: The title of the window.
  - **Returns**: A pointer to the created `Screen` object.

- `void Screen_destroy(Screen* screen)`
  - **Description**: Destroys the specified screen and frees associated resources.
  - **Parameters**:
    - `screen`: A pointer to the `Screen` object to be destroyed.

- `void Screen_clear(Screen* screen, uint32_t color)`
  - **Description**: Clears the screen with the specified color.
  - **Parameters**:
    - `screen`: A pointer to the `Screen` object.
    - `color`: The color to clear the screen with (in ARGB format).

- `void Screen_setPixel(Screen* screen, int x, int y, uint32_t color)`
  - **Description**: Sets the pixel at the specified coordinates to the specified color.
  - **Parameters**:
    - `screen`: A pointer to the `Screen` object.
    - `x`: The x-coordinate of the pixel.
    - `y`: The y-coordinate of the pixel.
    - `color`: The color to set the pixel to (in ARGB format).

- `void Screen_render(Screen* screen)`
  - **Description**: Renders the screen.
  - **Parameters**:
    - `screen`: A pointer to the `Screen` object.

- `void Screen_limitFrameRate(Screen* screen, int fps)`
  - **Description**: Limits the frame rate to the specified FPS.
  - **Parameters**:
    - `screen`: A pointer to the `Screen` object.
    - `fps`: The desired frame rate.

### 2. Map

The `Map` component is responsible for loading and managing the game map. It provides functions to load maps from files and check for collisions.

#### Functions

- `Map* Map_create(int width, int height)`
  - **Description**: Creates a new map with the specified width and height.
  - **Parameters**:
    - `width`: The width of the map.
    - `height`: The height of the map.
  - **Returns**: A pointer to the created `Map` object.

- `void Map_destroy(Map* map)`
  - **Description**: Destroys the specified map and frees associated resources.
  - **Parameters**:
    - `map`: A pointer to the `Map` object to be destroyed.

- `bool Map_load(Map* map, const char* filename)`
  - **Description**: Loads the map from the specified file.
  - **Parameters**:
    - `map`: A pointer to the `Map` object.
    - `filename`: The path to the map file.
  - **Returns**: `true` if the map was loaded successfully, `false` otherwise.

- `char Map_getTile(const Map* map, int x, int y)`
  - **Description**: Returns the tile at the specified coordinates.
  - **Parameters**:
    - `map`: A pointer to the `Map` object.
    - `x`: The x-coordinate of the tile.
    - `y`: The y-coordinate of the tile.
  - **Returns**: The tile character at the specified coordinates.

- `bool Map_checkCollision(const Map* map, float x, float y)`
  - **Description**: Checks for collisions at the specified coordinates.
  - **Parameters**:
    - `map`: A pointer to the `Map` object.
    - `x`: The x-coordinate to check.
    - `y`: The y-coordinate to check.
  - **Returns**: `true` if a collision is detected, `false` otherwise.

### 3. Player

The `Player` component is responsible for managing the player's position and direction. It provides functions to move and rotate the player.

#### Functions

- `Player* Player_create(float x, float y, float direction)`
  - **Description**: Creates a new player at the specified coordinates with the specified direction.
  - **Parameters**:
    - `x`: The initial x-coordinate of the player.
    - `y`: The initial y-coordinate of the player.
    - `direction`: The initial direction of the player (in radians).
  - **Returns**: A pointer to the created `Player` object.

- `void Player_destroy(Player* player)`
  - **Description**: Destroys the specified player and frees associated resources.
  - **Parameters**:
    - `player`: A pointer to the `Player` object to be destroyed.

- `void Player_move(Player* player, float distance, const Map* map)`
  - **Description**: Moves the player by the specified distance, taking into account collisions with the map.
  - **Parameters**:
    - `player`: A pointer to the `Player` object.
    - `distance`: The distance to move the player.
    - `map`: A pointer to the `Map` object.

- `void Player_rotate(Player* player, float angle)`
  - **Description**: Rotates the player by the specified angle.
  - **Parameters**:
    - `player`: A pointer to the `Player` object.
    - `angle`: The angle to rotate the player (in radians).

- `Point2D Player_getPosition(const Player* player)`
  - **Description**: Returns the player's current position.
  - **Parameters**:
    - `player`: A pointer to the `Player` object.
  - **Returns**: The player's current position as a `Point2D` structure.

- `Vector2D Player_getDirection(const Player* player)`
  - **Description**: Returns the player's current direction.
  - **Parameters**:
    - `player`: A pointer to the `Player` object.
  - **Returns**: The player's current direction as a `Vector2D` structure.

### 4. Raycaster

The `Raycaster` component is responsible for casting rays and rendering the 3D view. It provides functions to cast rays and draw vertical lines representing walls.

#### Functions

- `Raycaster* Raycaster_create(const Map* map, Screen* screen)`
  - **Description**: Creates a new raycaster with the specified map and screen.
  - **Parameters**:
    - `map`: A pointer to the `Map` object.
    - `screen`: A pointer to the `Screen` object.
  - **Returns**: A pointer to the created `Raycaster` object.

- `void Raycaster_destroy(Raycaster* raycaster)`
  - **Description**: Destroys the specified raycaster and frees associated resources.
  - **Parameters**:
    - `raycaster`: A pointer to the `Raycaster` object to be destroyed.

- `void Raycaster_castRays(Raycaster* raycaster, const Player* player)`
  - **Description**: Casts rays from the player's position and renders the 3D view.
  - **Parameters**:
    - `raycaster`: A pointer to the `Raycaster` object.
    - `player`: A pointer to the `Player` object.

- `float Raycaster_getDistanceToWall(const Raycaster* raycaster, float playerX, float playerY, float angle)`
  - **Description**: Returns the distance to the nearest wall in the specified direction.
  - **Parameters**:
    - `raycaster`: A pointer to the `Raycaster` object.
    - `playerX`: The x-coordinate of the player.
    - `playerY`: The y-coordinate of the player.
    - `angle`: The angle of the ray (in radians).
  - **Returns**: The distance to the nearest wall.

- `int Raycaster_calculateWallHeight(const Raycaster* raycaster, float distance)`
  - **Description**: Calculates the height of the wall at the specified distance.
  - **Parameters**:
    - `raycaster`: A pointer to the `Raycaster` object.
    - `distance`: The distance to the wall.
  - **Returns**: The height of the wall.

- `void Raycaster_drawVerticalLine(const Raycaster* raycaster, int x, int wallHeight, float distance)`
  - **Description**: Draws a vertical line representing a wall at the specified coordinates.
  - **Parameters**:
    - `raycaster`: A pointer to the `Raycaster` object.
    - `x`: The x-coordinate of the line.
    - `wallHeight`: The height of the wall.
    - `distance`: The distance to the wall.

### 5. Config

The `Config` component is responsible for loading and managing configuration settings. It provides functions to load configurations from files and retrieve configuration values.

#### Functions

- `Config* Config_create()`
  - **Description**: Creates a new configuration object.
  - **Returns**: A pointer to the created `Config` object.

- `void Config_destroy(Config* config)`
  - **Description**: Destroys the specified configuration object and frees associated resources.
  - **Parameters**:
    - `config`: A pointer to the `Config` object to be destroyed.

- `bool Config_load(Config* config, const char* filename)`
  - **Description**: Loads the configuration from the specified file.
  - **Parameters**:
    - `config`: A pointer to the `Config` object.
    - `filename`: The path to the configuration file.
  - **Returns**: `true` if the configuration was loaded successfully, `false` otherwise.

- `const char* Config_get(const Config* config, const char* key)`
  - **Description**: Returns the value associated with the specified key.
  - **Parameters**:
    - `config`: A pointer to the `Config` object.
    - `key`: The key to retrieve the value for.
  - **Returns**: The value associated with the specified key.

- `int Config_getInt(const Config* config, const char* key)`
  - **Description**: Returns the integer value associated with the specified key.
  - **Parameters**:
    - `config`: A pointer to the `Config` object.
    - `key`: The key to retrieve the value for.
  - **Returns**: The integer value associated with the specified key.

- `void Config_set(Config* config, const char* key, const char* value)`
  - **Description**: Sets the value associated with the specified key.
  - **Parameters**:
    - `config`: A pointer to the `Config` object.
    - `key`: The key to set the value for.
    - `value`: The value to set.

- `void Config_setInt(Config* config, const char* key, int value)`
  - **Description**: Sets the integer value associated with the specified key.
  - **Parameters**:
    - `config`: A pointer to the `Config` object.
    - `key`: The key to set the value for.
    - `value`: The integer value to set.

## Getting Started

To get started with Lexia Engine, you can use the LexiaEditor to create a new project. The editor will generate a basic project structure with initial code that demonstrates how to use the engine's components. You can then modify and expand the code to create your own game.

## Conclusion

Lexia Engine provides a solid foundation for creating 2.5D (Doom like) games with C and C++. Its modular design allows developers to easily extend and customize the engine to suit their specific needs. Whether you are a seasoned developer or an enthusiast, Lexia Engine offers the tools and flexibility to bring your game ideas to life.