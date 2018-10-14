CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(OpenGL)

#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g")

set(HEADER_FILES
    Application.h
    Camera.h
    Data.h
    FileRepository.h
    Framebuffer.h
    FrameGraph.h
    FrameObject.h
    GLFWApplication.h
    GLFWApplicationEvents.h
    Interface.h
    Helper.h
    Material.h
    Mesh.h
    Message.h
    Node.h
    Program.h
    Scene.h
    Selectable.h
    Shader.h
    ShaderProgram.h
    Texture.h
    Transform.h
    Viewer.h
    Visitor.h
    VisualManager.h
    VisualModel.h
    VisualOption.h
)

set(SOURCE_FILES
    Application.cpp
    Camera.cpp
    Data.cpp
    FileRepository.cpp
    Framebuffer.cpp
    FrameGraph.cpp
    FrameObject.cpp
    GLFWApplication.cpp
    GLFWApplicationEvents.cpp
    Interface.cpp
    Material.cpp
    Mesh.cpp
    Message.cpp
    Node.cpp
    Program.cpp
    Scene.cpp
    Selectable.cpp
    Shader.cpp
    ShaderProgram.cpp
    Texture.cpp
    Transform.cpp
    Viewer.cpp
    Visitor.cpp
    VisualManager.cpp
    VisualModel.cpp
    VisualOption.cpp
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
    shaders/highLight.gs
    shaders/highLight.fs
    shaders/matcap.vs
    shaders/matcap.fs
    shaders/normal.vs
    shaders/normal.gs
    shaders/normal.fs
    shaders/outline.vs
    shaders/outline.fs
    shaders/phongShading.vs
    shaders/phongShading.fs
    shaders/picking.vs
    shaders/picking.fs
    shaders/tangentSpace.vs
    shaders/tangentSpace.gs
    shaders/tangentSpace.fs
    shaders/texturing.vs
    shaders/texturing.fs
    shaders/vaoQuad.vs
    shaders/vaoQuad.fs
)

set(QRC_FILES
    resources.qrc
)

set(ARCHIVE_OUTPUT_DIRECTORY lib)
set(LIBRARY_OUTPUT_DIRECTORY lib)
set(RUNTIME_OUTPUT_DIRECTORY bin)

## Set the output directories globally
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY})

# Create etc/config.ini: it contains the paths to share/
# In the build directory, it points to the source tree
set(SHARE_DIR "${CMAKE_SOURCE_DIR}/share")
configure_file(${CMAKE_SOURCE_DIR}/etc/config.ini.in "${CMAKE_BINARY_DIR}/etc/config.ini")

# Required packages
find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Gui OpenGL REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(GLUT REQUIRED)

qt5_add_resources(RESOURCE_FILES ${QRC_FILES})

add_subdirectory(app)


#========== Creation of the library ==========#
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES} ${QRC_FILES} ${RESOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})# ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES} Qt5::Core Qt5::Gui Qt5::OpenGL)# ${GLEW_LIBRARIES} ${GLUT_LIBRARIES})


#========= Linking with local library =========#
macro(link_with_local_lib LOCAL_PATH NAME)
    set(${NAME}_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${LOCAL_PATH})

    find_library(${NAME}_LIBRARY
        NAME ${NAME}
        NO_DEFAULT_PATH
        PATHS ${${NAME}_PATH}/lib
    )

    if(${NAME}_LIBRARY-NOTFOUND)
        message(FATAL_ERROR "${NAME}_LIBRARY library not found !")
    else()
        target_include_directories(${PROJECT_NAME} PUBLIC ${${NAME}_PATH}/include)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${${NAME}_LIBRARY})
    endif()
endmacro()

link_with_local_lib(extlibs/glew GLEW)
link_with_local_lib(extlibs/GLFW glfw)
link_with_local_lib(extlibs/assimp assimp)
