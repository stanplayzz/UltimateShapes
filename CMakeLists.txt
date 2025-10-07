cmake_minimum_required(VERSION 3.15)
project(ultimateshapes LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(SFML)

file(GLOB ULTI_SOURCES "src/*.cpp")
add_library(ultimateshapes ${ULTI_SOURCES})
target_include_directories(ultimateshapes PUBLIC include)
target_compile_features(ultimateshapes PUBLIC cxx_std_23)
target_link_libraries(ultimateshapes PUBLIC SFML::Graphics SFML::Audio)