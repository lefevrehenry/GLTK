cmake_minimum_required(VERSION 3.2)
project(app)

set(HEADER_FILES
)

set(SOURCE_FILES
)

add_executable(${PROJECT_NAME} main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE OpenGL)
