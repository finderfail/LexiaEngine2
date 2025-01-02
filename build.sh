#!/bin/bash

# Пути
ENGINE_SRC_DIR="engine/src"
ENGINE_INCLUDE_DIR="engine/include"
ENGINE_LIB_DIR="lib"
EDITOR_SRC_DIR="editor/src"
EDITOR_BIN="editor/editor"

# ------------------------------------------------------------------------------
# Компиляция движка
echo "Компиляция движка..."

# Компилируем каждый cpp в .o
g++ -c $ENGINE_SRC_DIR/Screen.cpp -o $ENGINE_SRC_DIR/Screen.o -std=c++11
g++ -c $ENGINE_SRC_DIR/Map.cpp -o $ENGINE_SRC_DIR/Map.o -std=c++11
g++ -c $ENGINE_SRC_DIR/Player.cpp -o $ENGINE_SRC_DIR/Player.o -std=c++11
g++ -c $ENGINE_SRC_DIR/Raycaster.cpp -o $ENGINE_SRC_DIR/Raycaster.o -std=c++11
g++ -c $ENGINE_SRC_DIR/Config.cpp -o $ENGINE_SRC_DIR/Config.o -std=c++11

# Создаем статическую библиотеку
ar rcs $ENGINE_LIB_DIR/libengine.a $ENGINE_SRC_DIR/*.o 

if [ $? -ne 0 ]; then
    echo "Ошибка при компиляции движка."
    exit 1
fi

echo "Движок скомпилирован."

# ------------------------------------------------------------------------------
# Компиляция редактора
echo "Компиляция редактора..."
# g++ $EDITOR_SRC_DIR/*.cpp -o $EDITOR_BIN -I$ENGINE_INCLUDE_DIR $ENGINE_LIB_DIR/libengine.a

g++ -c $EDITOR_SRC_DIR/EditorWindow.cpp -o $EDITOR_SRC_DIR/EditorWindow.o -I$ENGINE_INCLUDE_DIR -std=c++11
g++ -c $EDITOR_SRC_DIR/MapEditor.cpp -o $EDITOR_SRC_DIR/MapEditor.o -I$ENGINE_INCLUDE_DIR -std=c++11
g++ -c $EDITOR_SRC_DIR/ConfigEditor.cpp -o $EDITOR_SRC_DIR/ConfigEditor.o -I$ENGINE_INCLUDE_DIR -std=c++11
g++ -c $EDITOR_SRC_DIR/ProjectManager.cpp -o $EDITOR_SRC_DIR/ProjectManager.o -I$ENGINE_INCLUDE_DIR -std=c++11
g++ -c $EDITOR_SRC_DIR/Compiler.cpp -o $EDITOR_SRC_DIR/Compiler.o -I$ENGINE_INCLUDE_DIR -std=c++11
g++ -c $EDITOR_SRC_DIR/main.cpp -o $EDITOR_SRC_DIR/main.o -I$ENGINE_INCLUDE_DIR -std=c++11


g++ $EDITOR_SRC_DIR/*.o -o $EDITOR_BIN $ENGINE_LIB_DIR/libengine.a -std=c++11
if [ $? -ne 0 ]; then
    echo "Ошибка при компиляции редактора."
    exit 1
fi

echo "Редактор скомпилирован."

# ------------------------------------------------------------------------------
echo "Компиляция завершена успешно!"