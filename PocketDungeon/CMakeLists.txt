# Specify CMake minimum version
cmake_minimum_required(VERSION 3.0)

#Project's name
project(PocketDungeon C CXX)

if (UNIX)
set (EXECUTABLE_OUTPUT_PATH ../)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE OFF)

#Find libraries

#Set sources

file(GLOB SOURCES "src/*.cpp" "src/OtterEngine/*.cpp" "src/MapManager/*.cpp" "src/Items/*.cpp" src/OtterEngine/SpriteManager/*.cpp src/Menu/*.cpp  "src/MapManager/MapObjects/*.cpp" "src/Pokemon/*.cpp" "src/Pokemon/Attacks/*.cpp" "src/Pokemon/Status/*.cpp" "src/OtterEngine/Music/*.cpp" "src/OtterEngine/GUI/*.cpp") #like wildcard

#Set headers
include_directories(include include/MapManager include/OtterEngine/SpriteManager include/Menu include/MapManager/MapObjects include/Pokemon include/Pokemon/Attacks include/Pokemon/Status include/OtterEngine/Music include/OtterEngine include/Items/ include/OtterEngine/GUI)

add_executable(PocketDungeon ${SOURCES} src/Camera.cpp include/Camera.h include/Pokemon/Attacks/VineWhip.h src/Pokemon/Attacks/VineWhip.cpp)

#target_link_libraries(PocketDungeon ${CMAKE_SOURCE_DIR}/libraries/irrlicht/lib/linux/libIrrlicht.a GL pthread ...)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED network audio graphics window system)
#find_package(SFML REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(PocketDungeon ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

endif (UNIX)
