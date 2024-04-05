cmake_minimum_required(VERSION 3.27)
project(WeatherApplication)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

set(BUILD_SHARED_LIBS OFF)
include(FetchContent)

FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui GIT_TAG v4.0.0)

FetchContent_MakeAvailable(ftxui)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)

add_executable(WeatherApplication main.cpp
        ConfigParseAndRequests/json_storage.h
        ConfigParseAndRequests/json_storage.cpp
        Interface/ConsoleInterface.h
        Interface/ConsoleInterface.cpp
)

target_link_libraries(WeatherApplication PRIVATE cpr::cpr)
target_link_libraries(WeatherApplication PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)
target_link_libraries(WeatherApplication PRIVATE nlohmann_json::nlohmann_json)
