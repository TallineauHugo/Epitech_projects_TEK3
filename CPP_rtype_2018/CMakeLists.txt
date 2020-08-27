cmake_minimum_required(VERSION 3.0)

#Project's name
project(R-Type C CXX)

set(EXECUTABLE_OUTPUT_PATH ../)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-W -Wextra -std=c++11")

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

#Set sources
file(GLOB CLIENT Client/src/*.cpp OtterEngine/src/*.cpp OtterEngine/src/Music/*.cpp OtterEngine/src/GUI/*.cpp OtterEngine/src/SpriteManager/*.cpp) #like wildcard
file(GLOB SERVER Server/src/*.cpp OtterEngine/src/*.cpp OtterEngine/src/Music/*.cpp OtterEngine/src/GUI/*.cpp OtterEngine/src/SpriteManager/*.cpp)

#Set headers
include_directories(Client/include OtterEngine/include/SpriteManager OtterEngine/include/Music OtterEngine/include/GUI OtterEngine/include Server/include)

add_executable(r-type_client ${CLIENT})
add_executable(r-type_server ${SERVER})
target_link_libraries(r-type_server ${CONAN_LIBS})
target_link_libraries(r-type_client ${CONAN_LIBS} sfml-window sfml-graphics sfml-network sfml-audio sfml-system)