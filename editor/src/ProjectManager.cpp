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
        mainFile << "#include \"../../engine/include/SDL/SDL.h\"\n\n";
        mainFile << "#define M_PI 3.14159265358979323846\n"; 
        mainFile << "#include <iostream>\n"; 
        mainFile << "#include <chrono>\n"; 
        mainFile << "#include <thread>\n\n"; 
        mainFile << "int main() {\n";
        mainFile << "  Config config;\n";
        mainFile << "  if (!config.load(\"" << currentProjectDir_ << "/config/game.conf\")) {\n";
        mainFile << "    return 1;\n";
        mainFile << "  }\n\n";
        mainFile << "  int screenWidth = config.getInt(\"screenWidth\");\n";
        mainFile << "  int screenHeight = config.getInt(\"screenHeight\");\n";
        mainFile << "  const char* gameName = \"Lexia Development Kit (LE2)\";\n";
        mainFile << "  Screen screen(screenWidth, screenHeight, gameName);\n\n";
        mainFile << "  Map map;\n";
        mainFile << "  if (!map.load(\"" << currentProjectDir_ << "/maps/map.txt\")) {\n";
        mainFile << "    return 1;\n";
        mainFile << "  }\n";
        mainFile << "  float playerStartX = config.getInt(\"playerStartX\");\n";
        mainFile << "  float playerStartY = config.getInt(\"playerStartY\");\n";
        mainFile << "  float playerStartDir = config.getInt(\"playerStartDir\") * M_PI / 180.0f;\n";
        mainFile << "  Player player(playerStartX, playerStartY, playerStartDir);\n";
        mainFile << "  Raycaster raycaster(map, screen);\n\n";
        mainFile << "  bool isRunning = true;\n";
        mainFile << "  SDL_Event event;\n";
        mainFile << "  while (isRunning) {\n";
        mainFile << "  while(SDL_PollEvent(&event))\n";
        mainFile << "    {\n";
        mainFile << "      if (event.type == SDL_QUIT)\n";
        mainFile << "        isRunning = false;\n";
        mainFile << "      if (event.type == SDL_KEYDOWN) {\n";
        mainFile << "        float moveSpeed = 0.1f;\n";
        mainFile << "        float rotateSpeed = 0.05f;\n";
        mainFile << "        switch (event.key.keysym.sym) {\n";
        mainFile << "          case SDLK_w:\n";
        mainFile << "             player.move(moveSpeed, map);\n";
        mainFile << "             break;\n";
        mainFile << "          case SDLK_s:\n";
        mainFile << "             player.move(-moveSpeed, map);\n";
        mainFile << "             break;\n";
        mainFile << "          case SDLK_a:\n";
        mainFile << "             player.rotate(-rotateSpeed);\n";
        mainFile << "             break;\n";
        mainFile << "          case SDLK_d:\n";
        mainFile << "             player.rotate(rotateSpeed);\n";
        mainFile << "             break;\n";
        mainFile << "          case SDLK_q:\n";
        mainFile << "             isRunning = false;\n";
        mainFile << "             break;\n";
        mainFile << "          default:\n";
        mainFile << "             break;\n";
        mainFile << "        }\n";
        mainFile << "      }\n";
        mainFile << "  }\n\n";
        mainFile << "  screen.clear(0x000000);\n";
        mainFile << "  raycaster.castRays(player);\n";
        mainFile << "  screen.render();\n";
        mainFile << "  std::this_thread::sleep_for(std::chrono::milliseconds(16));\n";
        mainFile << "      }\n";
        mainFile << "  return 0;\n";
        mainFile << "      }\n";
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