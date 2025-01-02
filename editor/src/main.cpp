#include "EditorWindow.h"
#include "MapEditor.h"
#include "ConfigEditor.h"
#include "ProjectManager.h"
#include "Compiler.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

void clearScreen() {
    std::cout << "\033[2J\033[H";
}


int main() {
    int screenWidth = 120;
    int screenHeight = 30;
    EditorWindow window(screenWidth, screenHeight, "Game Editor");
    ProjectManager projectManager;
    Compiler compiler;
    std::string currentProjectDir;
     std::string input;
    while(true)
    {
        clearScreen();
        std::cout << "1. Create new project" << std::endl;
        std::cout << "2. Load project" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: " << std::endl;

        std::cin >> input;
        if (input == "1")
        {
            clearScreen();
            std::string projectName;
            std::cout << "Enter the name of the new project:" << std::endl;
            std::cin >> projectName;
            if(projectManager.createProject(projectName))
            {
                currentProjectDir = projectManager.getCurrentProjectDir();
                std::cout << "Project created in " << currentProjectDir << std::endl;
                break;
            }
        } else if (input == "2")
        {
           clearScreen();
            std::string projectName;
            std::cout << "Enter the name of the project you want to load:" << std::endl;
             std::cin >> projectName;
            
            std::ifstream file(projectName + "/project.conf");
            if (!file.is_open())
            {
                std::cerr << "Could not find project file!" << std::endl;
                continue;
            }
             std::string line;
           std::getline(file, line);
            file.close();
             
            if (projectManager.loadProject(line))
            {
                currentProjectDir = projectManager.getCurrentProjectDir();
                std::cout << "Project loaded from " << currentProjectDir << std::endl;
                break;
            }

        }
        else if(input == "3")
            return 0;
        else
        {
            std::cerr << "Invalid input!" << std::endl;
        }
    }
    
    while(true)
    {
        clearScreen();
        std::cout << "1. Map Editor" << std::endl;
        std::cout << "2. Config Editor" << std::endl;
        std::cout << "3. Compile Project" << std::endl;
        std::cout << "4. Run Project" << std::endl;
        std::cout << "5. Back" << std::endl;
        std::cout << "Enter your choice: " << std::endl;
        std::cin >> input;
        if (input == "1")
        {
            MapEditor mapEditor(window);
            mapEditor.loadMap(currentProjectDir + "/maps/map.txt");
            mapEditor.run();
            mapEditor.saveMap(currentProjectDir + "/maps/map.txt");
        } else if (input == "2")
        {
            ConfigEditor configEditor(window);
             configEditor.loadConfig(currentProjectDir + "/config/game.conf");
              configEditor.run();
            configEditor.saveConfig(currentProjectDir + "/config/game.conf");
        } else if (input == "3")
        {
            if(!compiler.compileProject(currentProjectDir))
            {
                std::cerr << "Error: Project did not compile!" << std::endl;
            }
             std::getchar();
        }
        else if (input == "4")
        {
            std::string gamePath = projectManager.getGameBuildPath();
             std::string command = gamePath + "/game";
            int status = system(command.c_str());
               if (status == -1)
               {
                   std::cerr << "Error: Could not execute game!" << std::endl;
               }
                std::getchar();
        }
         else if (input == "5")
        {
           break;
        }
       else
        {
            std::cerr << "Invalid input!" << std::endl;
        }
    }

    return 0;
}