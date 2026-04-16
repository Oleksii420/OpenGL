cmake_minimum_required(VERSION 4.2)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)



find_package(OpenGL REQUIRED)

set(libs
        ${OPENGL_LIBRARY}
        glad
        glfw
        glm
)

#[[add_executable(${PROJECT_NAME} src/laba/main.cpp
        src/utils/shader_utils.cpp
        src/utils/shader_utils.h)
target_link_libraries(${PROJECT_NAME} ${libs})]]

set(UTILS_DIR src/utils)
file(GLOB_RECURSE UTILS_SRC
        ${UTILS_DIR}/*.cpp
        ${UTILS_DIR}/*.h)

set(LABA_TARGET laba)
set(LABA_DIR src/${LABA_TARGET})

file(GLOB_RECURSE  LABA_SRC
        ${LABA_DIR}/*.cpp
        ${LABA_DIR}/*.h
)

add_executable(${LABA_TARGET}
        ${LABA_SRC}
        ${UTILS_SRC})

target_link_libraries(${LABA_TARGET} ${libs})
target_include_directories(${LABA_TARGET} PRIVATE ${UTILS_DIR})

add_custom_command(TARGET ${LABA_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${LABA_DIR}/res
        $<TARGET_FILE_DIR:${LABA_TARGET}>/res)
