#include "Compiler.h"
#include "ProjectManager.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

Compiler::Compiler() {}
Compiler::~Compiler() {}

bool Compiler::compileProject(const std::string& projectDir)
{
    ProjectManager manager;

    std::string srcPath = "./" + projectDir + "/src";
    std::string buildPath = "./" + projectDir + "/build";
    std::string engineInc = "engine/include";
    std::string engineLib = "./lib/libengine.a";
    #ifdef __APPLE__ 
        std::string command = "g++ " + srcPath + "/main.cpp " + engineLib + " -I" + engineInc + " -o " + buildPath + "/game" + " -F/Library/Frameworks -framework SDL2 -I/usr/local/Cellar/sdl2/2.30.11/include -L/usr/local/Cellar/sdl2/2.30.11/lib";
    #elif defined(__linux__)
        std::string command = "g++ " + srcPath + "/main.cpp " + engineLib + " -I" + engineInc + " -o " + buildPath + "/game" + " -lSDL2";
    #endif
    std::cerr << "Complication command: " << command << std::endl;
    int status = system(command.c_str());
     if (status == -1)
      {
          std::cerr << "Error: Could not execute compilation command!" << std::endl;
          return false;
      }
      else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
      {
          std::cerr << "Error: Compilation failed with exit code " << WEXITSTATUS(status) << std::endl;
          return false;
      }
      std::cout << "Success: Project has been compiled!" << std::endl;
    return true;
}