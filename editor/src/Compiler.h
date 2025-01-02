#ifndef COMPILER_H
#define COMPILER_H

#include <string>

class Compiler {
public:
    Compiler();
    ~Compiler();
    bool compileProject(const std::string& projectDir);

private:
};

#endif