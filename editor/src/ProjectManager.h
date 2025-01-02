#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <string>
#include <vector>
class ProjectManager {
public:
    ProjectManager();
    ~ProjectManager();
    bool createProject(const std::string& projectName);
    bool loadProject(const std::string& projectName);
    void setCurrentProjectDir(const std::string& dir);
    std::string getCurrentProjectDir();
    std::string getGameSourcePath();
    std::string getGameBuildPath();
    void saveProjectConfig();
private:
  std::string currentProjectDir_;
};

#endif