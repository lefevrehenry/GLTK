cmake_minimum_required(VERSION 3.2)
project(app)

set(EXECUTABLE_FILES
    deferredShading
    environmentMapping
    normalMapping
    picking
)

find_package(glfw3 CONFIG REQUIRED)

foreach(exec ${EXECUTABLE_FILES})
    add_executable(${exec} ${exec}.cpp)
    target_include_directories(${exec} PRIVATE ${CMAKE_SOURCE_DIR} ${GLFW3_INCLUDE_DIR})
    target_link_libraries(${exec} LINK_PRIVATE OpenGL ${GLFW3_LIBRARY})
endforeach()

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${GLFW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE OpenGL ${GLFW3_LIBRARY})
