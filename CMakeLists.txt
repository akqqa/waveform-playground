cmake_minimum_required(VERSION 3.28)
project(Waveform_playground)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(waveform_playground src/main.cpp src/Grid.cpp src/MouseHandler.cpp src/SoundHandler.cpp)
target_compile_features(waveform_playground PRIVATE cxx_std_17)
target_link_libraries(waveform_playground PRIVATE 
    SFML::Graphics 
    SFML::Audio 
    SFML::System
)
