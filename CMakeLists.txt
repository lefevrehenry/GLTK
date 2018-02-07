CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(OpenGL)

set(CMAKE_BUILD_TYPE RELEASE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#file(GLOB_RECURSE HEADER_FILES include/*.hpp)
#file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.tpp)
#file(GLOB_RECURSE SHADER_FILES shaders/*.glsl)

set(HEADER_FILES
    Application.h
    Camera.h
    Data.h
    Data.inl
    GLFWApplicationEvents.h
    Helper.h
    GLFWApplication.h
    Mesh.h
    Message.h
    Program.h
    Shader.h
    ShaderProgram.h
)

set(SOURCE_FILES
    Application.cpp
    Camera.cpp
    Data.cpp
    GLFWApplicationEvents.cpp
    GLFWApplication.cpp
    Mesh.cpp
    Message.cpp
    Program.cpp
    Shader.cpp
    ShaderProgram.cpp
    main.cpp
)

set(SHADER_FILES
    shaders/basic.vs
    shaders/basic.gs
    shaders/basic.fs
    shaders/normal.vs
    shaders/normal.gs
    shaders/normal.fs
)

# Required packages
find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(GLUT REQUIRED)

#========== Creation of the library ==========#
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})# ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES})# ${GLEW_LIBRARIES} ${GLUT_LIBRARIES})

target_compile_definitions(${PROJECT_NAME} PRIVATE USE_GLUT)

#========= Linking with local Glew =========#
set(GLEW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/glew)

find_library(GLEW_LIBRARY
    NAME GLEW
    NO_DEFAULT_PATH
    PATHS ${GLEW_PATH}/lib
)

if(GLEW_LIBRARY-NOTFOUND)
    message(FATAL_ERROR "GLFW_LIBRARY library not found !")
else()
    target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_PATH}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${GLEW_LIBRARY})
endif()

#========= Linking with local GLFW =========#
set(GLFW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/GLFW)

find_library(GLFW_LIBRARY
    NAME glfw
    NO_DEFAULT_PATH
    PATHS ${GLFW_PATH}/lib
)

if(GLFW_LIBRARY-NOTFOUND)
    message(FATAL_ERROR "GLFW_LIBRARY library not found !")
else()
    target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_PATH}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW_LIBRARY})
endif()

#======== Linking with local Freeglut ========#
set(FREEGLUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/freeglut)

find_library(FREEGLUT_LIBRARY
    NAME glut
    NO_DEFAULT_PATH
    PATHS ${FREEGLUT_PATH}/lib
)

if(FREEGLUT_LIBRARY-NOTFOUND)
    message(FATAL_ERROR "Freeglut library not found !")
else()
    target_include_directories(${PROJECT_NAME} PUBLIC ${FREEGLUT_PATH}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${FREEGLUT_LIBRARY})
endif()

#========= Linking with local Assimp =========#
set(ASSIMP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/assimp)

find_library(ASSIMP_LIBRARY
    NAME assimp
    NO_DEFAULT_PATH
    PATHS ${ASSIMP_PATH}/lib
)

if(ASSIMP_LIBRARY-NOTFOUND)
    message(FATAL_ERROR "Assimp library not found !")
else()
    target_include_directories(${PROJECT_NAME} PUBLIC ${ASSIMP_PATH}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${ASSIMP_LIBRARY})
endif()
