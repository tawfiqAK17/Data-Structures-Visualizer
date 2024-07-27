cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DataStructuresVisualizer VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the SFML package with required components
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(DataStructuresVisualizer main.cpp
        UI/MainWindow.cpp
        UI/ArrayVisualizer.cpp
        UI/NodeRect.cpp
        UI/Button.cpp
        DataStructures/DataStructure.cpp
        DataStructures/DataStructure.hpp
        UI/Visualizer.cpp
        UI/Visualizer.hpp
        UI/TextHolder.cpp
        UI/TextHolder.hpp
        DataStructures/Array.cpp
        DataStructures/Array.hpp
)

# Include SFML directories
target_include_directories(DataStructuresVisualizer PRIVATE ${SFML_INCLUDE_DIRS})

# Link SFML libraries to the executable
target_link_libraries(DataStructuresVisualizer PRIVATE sfml-graphics sfml-window sfml-system)