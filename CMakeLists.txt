cmake_minimum_required(VERSION 3.28.0)

set(PROJECT_NAME pokesdl)

project(${PROJECT_NAME} LANGUAGES CXX)

set(SOURCES src/main.cpp src/Game.cpp src/Console.cpp src/Textbox.cpp src/TextureManager.cpp src/GameObject.cpp src/Player.cpp src/Pokemon.cpp src/PokemonStorage.cpp src/Ball.cpp)

include_directories(lib/SDL2/include lib/SDL2Image/include lib/SDL2TTF/include)

link_directories(lib/SDL2/lib lib/SDL2Image/lib lib/SDL2TTF/lib)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE mingw32 SDL2Main SDL2 SDL2_image SDL2_ttf)



