cmake_minimum_required(VERSION 3.18)

project(game_of_ur)

include(FetchContent)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES= ${X11_LIBRARIES}")

include_directories(${X11_INCLUDE_DIR})

link_directories(${X11_LIBRARIES})


add_executable(gameofur src/main.cpp)


target_link_libraries(gameofur PRIVATE sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json ${X11_LIBRARIES})

target_compile_features(gameofur PRIVATE cxx_std_17)

add_custom_command(TARGET gameofur POST_BUILD COMMAND notify-send "Compiled!" "Your binary is ready ^-^")

install(TARGETS gameofur RUNTIME DESTINATION bin)
