add_subdirectory(glfw)

add_subdirectory(glad)

add_library(glm INTERFACE
        ../src/laba04/main.cpp)
target_include_directories(glm INTERFACE glm)