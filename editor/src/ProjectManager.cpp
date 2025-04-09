#include "ProjectManager.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>

ProjectManager::ProjectManager() : currentProjectDir_("") {}
ProjectManager::~ProjectManager() {}

bool ProjectManager::createProject(const std::string& projectName)
{
    currentProjectDir_ = "./" + projectName;
    std::string gameSrcDir = currentProjectDir_ + "/src";
    std::string gameBuildDir = currentProjectDir_ + "/build";
    std::string mapDir = currentProjectDir_ + "/maps";
    std::string configDir = currentProjectDir_ + "/config";
    std::cerr << "Creating root dir: " << currentProjectDir_ << std::endl;
    if (mkdir(currentProjectDir_.c_str(), 0777) != 0) {
      std::cerr << "Error: Could not create root directory: " << projectName << std::endl;
        return false;
    }
    std::cerr << "Creating gameSrcDir: " << gameSrcDir << std::endl;
    if (mkdir(gameSrcDir.c_str(), 0777) != 0) {
      std::cerr << "Error: Could not create source directory: " << projectName << std::endl;
       rmdir(currentProjectDir_.c_str());
        return false;
    }
     std::cerr << "Creating gameBuildDir: " << gameBuildDir << std::endl;
    if (mkdir(gameBuildDir.c_str(), 0777) != 0) {
         std::cerr << "Error: Could not create build directory: " << projectName << std::endl;
         rmdir(currentProjectDir_.c_str());
         rmdir(gameSrcDir.c_str());
         return false;
    }
     std::cerr << "Creating mapDir: " << mapDir << std::endl;
    if (mkdir(mapDir.c_str(), 0777) != 0) {
         std::cerr << "Error: Could not create map directory: " << projectName << std::endl;
         rmdir(currentProjectDir_.c_str());
          rmdir(gameSrcDir.c_str());
         rmdir(gameBuildDir.c_str());
         return false;
    }
      std::cerr << "Creating configDir: " << configDir << std::endl;
    if (mkdir(configDir.c_str(), 0777) != 0) {
          std::cerr << "Error: Could not create config directory: " << projectName << std::endl;
         rmdir(currentProjectDir_.c_str());
          rmdir(gameSrcDir.c_str());
          rmdir(gameBuildDir.c_str());
        rmdir(mapDir.c_str());
         return false;
    }

    saveProjectConfig();
    std::ofstream mainFile(gameSrcDir + "/main.cpp");
    if(mainFile.is_open())
    {
        mainFile << "#include \"../../engine/include/Screen.h\"\n";
        mainFile << "#include \"../../engine/include/Map.h\"\n";
        mainFile << "#include \"../../engine/include/Player.h\"\n";
        mainFile << "#include \"../../engine/include/Raycaster.h\"\n";
        mainFile << "#include \"../../engine/include/Config.h\"\n";
        mainFile << "#include <SDL.h>\n\n";
        mainFile << "#define M_PI 3.14159265358979323846\n";
        mainFile << "#include <iostream>\n";
        mainFile << "#include <chrono>\n";
        mainFile << "#include <thread>\n\n";
        mainFile << "int main() {\n";
        mainFile << "    Config config;\n";
        mainFile << "    if (!config.load(\"" << currentProjectDir_ << "/config/game.conf\")) {\n";
        mainFile << "        return 1;\n";
        mainFile << "    }\n\n";
        mainFile << "    int screenWidth = config.getInt(\"screenWidth\");\n";
        mainFile << "    int screenHeight = config.getInt(\"screenHeight\");\n";
        mainFile << "    const char* gameName = \"Lexia Development Kit (LE2)\";\n";
        mainFile << "    Screen* screen = Screen_create(screenWidth, screenHeight, gameName);\n\n";
        mainFile << "    Map* map = Map_create(20, 20);\n";
        mainFile << "    if (!Map_load(map, \"" << currentProjectDir_ << "/maps/map.txt\")) {\n";
        mainFile << "        return 1;\n";
        mainFile << "    }\n";
        mainFile << "    float playerStartX = config.getInt(\"playerStartX\");\n";
        mainFile << "    float playerStartY = config.getInt(\"playerStartY\");\n";
        mainFile << "    float playerStartDir = config.getInt(\"playerStartDir\") * M_PI / 180.0f;\n";
        mainFile << "    Player* player = Player_create(playerStartX, playerStartY, playerStartDir);\n";
        mainFile << "    Raycaster* raycaster = Raycaster_create(map, screen);\n\n";
        mainFile << "    bool running = true;\n";
        mainFile << "    SDL_Event event;\n";
        mainFile << "    while (running) {\n";
        mainFile << "        while (SDL_PollEvent(&event)) {\n";
        mainFile << "            if (event.type == SDL_QUIT) {\n";
        mainFile << "                running = false;\n";
        mainFile << "            }\n";
        mainFile << "        }\n\n";
        mainFile << "        // Обработка ввода\n";
        mainFile << "        const Uint8* state = SDL_GetKeyboardState(NULL);\n";
        mainFile << "        float moveSpeed = 0.1f;\n";
        mainFile << "        float rotateSpeed = 0.05f;\n\n";
        mainFile << "        if (state[SDL_SCANCODE_W]) {\n";
        mainFile << "            Player_move(player, moveSpeed, map);\n";
        mainFile << "        }\n";
        mainFile << "        if (state[SDL_SCANCODE_S]) {\n";
        mainFile << "            Player_move(player, -moveSpeed, map);\n";
        mainFile << "        }\n";
        mainFile << "        if (state[SDL_SCANCODE_A]) {\n";
        mainFile << "            Player_rotate(player, -rotateSpeed);\n";
        mainFile << "        }\n";
        mainFile << "        if (state[SDL_SCANCODE_D]) {\n";
        mainFile << "            Player_rotate(player, rotateSpeed);\n";
        mainFile << "        }\n\n";
        mainFile << "        Screen_clear(screen, 0x000000);\n";
        mainFile << "        Raycaster_castRays(raycaster, player);\n";
        mainFile << "        Screen_render(screen);\n";
        mainFile << "        Screen_limitFrameRate(screen, 120);\n";
        mainFile << "    }\n\n";
        mainFile << "    Raycaster_destroy(raycaster);\n";
        mainFile << "    Player_destroy(player);\n";
        mainFile << "    Map_destroy(map);\n";
        mainFile << "    Screen_destroy(screen);\n\n";
        mainFile << "    return 0;\n";
        mainFile << "}\n";
        mainFile.close();
    }

    std::ofstream confFile(currentProjectDir_ + "/config/game.conf");
    if (confFile.is_open()) {
        confFile << "screenWidth=1280\n";
        confFile << "screenHeight=720\n";
        confFile << "playerStartX=3.0\n";
        confFile << "playerStartY=3.0\n";
        confFile << "playerStartDir=90\n";
        confFile.close();
    }
    std::ofstream mapFile(currentProjectDir_ + "/maps/map.txt");
     if (mapFile.is_open()) {
        mapFile << "################################\n";
        mapFile << "#                              #\n";
        mapFile << "#                              #\n";
        mapFile << "#                              #\n";
        mapFile << "#  #####                       #\n";
        mapFile << "#  #   #                       #\n";
        mapFile << "#  #   #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "#      #                       #\n";
        mapFile << "################################\n";
        mapFile.close();
     }

    return true;
}

bool ProjectManager::loadProject(const std::string& projectName) {
  currentProjectDir_ = projectName;
  return true;
}

void ProjectManager::setCurrentProjectDir(const std::string& dir) {
    currentProjectDir_ = dir;
}
std::string ProjectManager::getCurrentProjectDir() {
    return currentProjectDir_;
}
std::string ProjectManager::getGameSourcePath()
{
  return currentProjectDir_ + "/src";
}
std::string ProjectManager::getGameBuildPath()
{
    return currentProjectDir_ + "/build";
}
void ProjectManager::saveProjectConfig()
{
   std::ofstream file(currentProjectDir_ + "/project.conf");
   if (file.is_open())
   {
    file << currentProjectDir_ << std::endl;
    file.close();
   } else {
      std::cerr << "Error: Could not save project config!" << std::endl;
   }
}