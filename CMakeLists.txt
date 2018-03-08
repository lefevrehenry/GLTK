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
    FileRepository.h
#    Framebuffer.h
	GLFWApplication.h
    GLFWApplicationEvents.h
    Interface.h
    Helper.h
    Mesh.h
    Message.h
    Program.h
    Scene.h
    Shader.h
    ShaderProgram.h
    Texture.h
    Transform.h
)

set(SOURCE_FILES
    Application.cpp
    Camera.cpp
    Data.cpp
    FileRepository.cpp
#    Framebuffer.cpp
    GLFWApplication.cpp
    GLFWApplicationEvents.cpp
    Interface.cpp
    Mesh.cpp
    Message.cpp
    Program.cpp
    Scene.cpp
    Shader.cpp
    ShaderProgram.cpp
    Texture.cpp
    Transform.cpp
)

set(SHADER_FILES
    shaders/basic.vs
    shaders/basic.gs
    shaders/basic.fs
    shaders/flatShading.vs
    shaders/flatShading.gs
    shaders/flatShading.fs
    shaders/frame.vs
    shaders/frame.fs
    shaders/gouraudShading.vs
    shaders/gouraudShading.fs
    shaders/highLight.vs
    shaders/highLight.fs
    shaders/normal.vs
    shaders/normal.gs
    shaders/normal.fs
    shaders/phongShading.vs
    shaders/phongShading.fs
    shaders/tangentSpace.vs
    shaders/tangentSpace.gs
    shaders/tangentSpace.fs
    shaders/texturing.vs
    shaders/texturing.fs
)

set(QRC_FILES
    resources.qrc
)

# set(SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/share")

# Required packages
find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Gui OpenGL REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(GLUT REQUIRED)

qt5_add_resources(RESOURCE_FILES ${QRC_FILES})

add_subdirectory(app)

#========== Creation of the library ==========#
#add_executable(${PROJECT_NAME} main.cpp ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES} ${QRC_FILES} ${RESOURCE_FILES})

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES} ${QRC_FILES} ${RESOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})# ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES} Qt5::Core Qt5::Gui Qt5::OpenGL)# ${GLEW_LIBRARIES} ${GLUT_LIBRARIES})

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
