cmake_minimum_required(VERSION 3.2)
project(app)

set(EXECUTABLE_FILES
    environmentMapping
    normalMapping
    picking
)

foreach(exec_i ${EXECUTABLE_FILES})
    add_executable(${exec_i} ${exec_i}.cpp)
    target_include_directories(${exec_i} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${exec_i} LINK_PRIVATE OpenGL)
endforeach()

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE OpenGL)
