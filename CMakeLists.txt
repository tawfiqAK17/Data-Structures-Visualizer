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
        UI/Visualizers/ArrayVisualizer.cpp
        UI/UIElements/NodeRect.cpp
        UI/UIElements/Button.cpp
        DataStructures/DataStructure.cpp
        UI/Visualizers/Visualizer.cpp
        UI/UIElements/TextHolder.cpp
        DataStructures/Array.cpp
        UI/UIElements/StaticText.cpp
        DataStructures/LinkedList.cpp
        UI/Visualizers/LinkedListVisualizer.cpp
        UI/UIElements/Arrow.cpp
        DataStructures/BinarySearchTree.cpp
        UI/Visualizers/BinarySearchTreeVisualizer.cpp
        DataStructures/AvlTree.cpp
        UI/Visualizers/AvlTreeVisualizer.cpp
)

# Include SFML directories
target_include_directories(DataStructuresVisualizer PRIVATE ${SFML_INCLUDE_DIRS})

# Link SFML libraries to the executable
target_link_libraries(DataStructuresVisualizer PRIVATE sfml-graphics sfml-window sfml-system)
