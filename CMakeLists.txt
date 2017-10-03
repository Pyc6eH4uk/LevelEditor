set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

cmake_minimum_required(VERSION 3.7)
project(foaleditor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp source/Grass.cpp source/Grass.h source/GridItemBuilder.cpp source/GridItemBuilder.h source/SceneGraphicsView.cpp source/SceneGraphicsView.h source/EditorWindow.cpp source/EditorWindow.h source/LevelSettingDialog.cpp source/LevelSettingDialog.h source/Bonus.cpp source/Bonus.h source/GridItem.cpp source/GridItem.h source/Objects.cpp source/Objects.h)
add_executable(foaleditor ${SOURCE_FILES} resource.qrc)

# qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH /home/gdhsnlvr/Qt/5.9/gcc_64/lib/cmake)
find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5OpenGL REQUIRED )
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL )