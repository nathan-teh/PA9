cmake_minimum_required(VERSION 3.28)
project(PA9 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
        src/main.cpp
        src/Player.cpp
        src/Player.h
        src/Platform.cpp
        src/Platform.h
        src/Collider.cpp
        src/Collider.h
        src/Animation.cpp
        src/Animation.h
        src/Map.cpp
        src/Map.h
        src/Camera.cpp
        src/Camera.h
        src/Button.hpp
        src/TestFunctions.cpp
        src/TestFunctions.h
        src/Music.h
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE SFML::Audio)
# For MSVC (Windows), link the ws2_32 library
if(MSVC)
    target_link_libraries(main PRIVATE ws2_32)
endif()