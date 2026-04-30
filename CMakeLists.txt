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


set(UTILS_DIR src/utils)

file(GLOB_RECURSE UTILS_SRC CONFIGURE_DEPENDS
        "${UTILS_DIR}/*.cpp"
        "${UTILS_DIR}/*.h")


function(add_lab TARGET_NAME)
    set(LAB_DIR "src/${TARGET_NAME}")

    file(GLOB_RECURSE LAB_SRC CONFIGURE_DEPENDS
            "${LAB_DIR}/*.cpp"
            "${LAB_DIR}/*.h"
    )

    add_executable(${TARGET_NAME} ${LAB_SRC} ${UTILS_SRC})

    target_link_libraries(${TARGET_NAME} PRIVATE ${libs})
    target_include_directories(${TARGET_NAME} PRIVATE ${UTILS_DIR})


    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/${LAB_DIR}/res"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/res")
endfunction()

add_lab(laba)
add_lab(laba01)
add_lab(laba02)