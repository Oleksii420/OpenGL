add_subdirectory(glfw)

add_subdirectory(glad)

add_library(glm INTERFACE
        ../src/laba04/main.cpp
        ../src/utils/load_obj.h)
target_include_directories(glm INTERFACE glm)