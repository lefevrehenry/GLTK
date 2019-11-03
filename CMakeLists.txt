CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(GLTK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g")

set(HEADER_FILES
    src/controller/Controller.h

    src/graph/BoundingBoxVisitor.h
    src/graph/CubeMapTexture.h
    src/graph/DrawVisitor.h
    src/graph/DrawWithSelectionVisitor.h
    src/graph/FetchVisualModelVisitor.h
    src/graph/Mesh.h
    src/graph/Node.h
    src/graph/PickingVisitor.h
    src/graph/SceneGraph.h
    src/graph/ShaderProgram.h
    src/graph/ShaderVisitor.h
    src/graph/Texture.h
    src/graph/Texture2D.h
    src/graph/TexturedVisualModel.h
    src/graph/Visitor.h
    src/graph/VisualModel.h

    src/gui/SceneView.h

    src/helper/Message.h
    src/helper/FileRepository.h

    src/misc/Application.h
    src/misc/Camera.h
    src/misc/Light.h
    src/misc/Material.h
    src/misc/Rect.h
    src/misc/Transform.h

    src/gltk.h
)

set(SOURCE_FILES
    src/controller/Controller.cpp

    src/graph/BoundingBoxVisitor.cpp
    src/graph/CubeMapTexture.cpp
    src/graph/DrawVisitor.cpp
    src/graph/DrawWithSelectionVisitor.cpp
    src/graph/FetchVisualModelVisitor.cpp
    src/graph/Mesh.cpp
    src/graph/Node.cpp
    src/graph/PickingVisitor.cpp
    src/graph/SceneGraph.cpp
    src/graph/ShaderProgram.cpp
    src/graph/ShaderVisitor.cpp
    src/graph/Texture.cpp
    src/graph/Texture2D.cpp
    src/graph/TexturedVisualModel.cpp
    src/graph/Visitor.cpp
    src/graph/VisualModel.cpp

    src/gui/SceneView.cpp

    src/helper/FileRepository.cpp
    src/helper/Message.cpp

    src/misc/Application.cpp
    src/misc/Camera.cpp
    src/misc/Light.cpp
    src/misc/Material.cpp
    src/misc/Rect.cpp
    src/misc/Transform.cpp

    src/gltk.cpp
)

set(PRIVATE_HEADER_FILES
    src/opengl/CubeMapTexturePrivate.h
    src/opengl/Data.h
    src/opengl/Framebuffer.h
    src/opengl/MeshPrivate.h
    src/opengl/Shader.h
    src/opengl/ShaderProgramPrivate.h
    src/opengl/TexturePrivate.h
    src/opengl/TexturePrivate2D.h
    src/opengl/VisualManager.h
    src/opengl/VisualOption.h

    src/statemachine/OpenGLAttribute.h
    src/statemachine/OpenGLStateMachine.h
)

set(PRIVATE_SOURCE_FILES
    src/opengl/CubeMapTexturePrivate.cpp
    src/opengl/Data.cpp
    src/opengl/Framebuffer.cpp
    src/opengl/MeshPrivate.cpp
    src/opengl/Shader.cpp
    src/opengl/ShaderProgramPrivate.cpp
    src/opengl/TexturePrivate.cpp
    src/opengl/TexturePrivate2D.cpp
    src/opengl/VisualManager.cpp
    src/opengl/VisualOption.cpp

    src/statemachine/OpenGLAttribute.cpp
    src/statemachine/OpenGLAttribute.inl
    src/statemachine/OpenGLStateMachine.cpp
    src/statemachine/OpenGLStateMachine.inl
)

set(EXTLIBS_SOURCE_FILES
    extlibs/glad/src/glad.c
)

set(SHADER_FILES
    share/shaders/basic.vs
    share/shaders/basic.fs
    share/shaders/basicTexturing.vs
    share/shaders/basicTexturing.fs
    share/shaders/cubeMap.vs
    share/shaders/cubeMap.fs
    share/shaders/deferred.vs
    share/shaders/deferred.fs
    share/shaders/environmentMapping.vs
    share/shaders/environmentMapping.fs
    share/shaders/flatShading.vs
    share/shaders/flatShading.gs
    share/shaders/flatShading.fs
    share/shaders/frame.vs
    share/shaders/frame.fs
    share/shaders/gouraudShading.vs
    share/shaders/gouraudShading.fs
    share/shaders/highLight.vs
    share/shaders/highLight.gs
    share/shaders/highLight.fs
    share/shaders/matcap.vs
    share/shaders/matcap.fs
    share/shaders/normal.vs
    share/shaders/normal.gs
    share/shaders/normal.fs
    share/shaders/normalMapping.vs
    share/shaders/normalMapping.fs
    share/shaders/outline.vs
    share/shaders/outline.fs
    share/shaders/phongShading.vs
    share/shaders/phongShading.fs
    share/shaders/picking.vs
    share/shaders/picking.fs
    share/shaders/shadowMapping.vs
    share/shaders/shadowMapping.fs
    share/shaders/tangentSpace.vs
    share/shaders/tangentSpace.gs
    share/shaders/tangentSpace.fs
    share/shaders/texturing.vs
    share/shaders/texturing.fs
    share/shaders/transform.vs
    share/shaders/transform.fs
    share/shaders/vaoQuad.vs
    share/shaders/vaoQuad.fs
)

set(CONFIG_FILES
    etc/config.ini.in
)

set(BUILD_EXAMPLES ON CACHE BOOL "")
set(BUILD_WITH_GLFW ON CACHE BOOL "")

set(ARCHIVE_OUTPUT_DIRECTORY lib)
set(LIBRARY_OUTPUT_DIRECTORY lib)
set(RUNTIME_OUTPUT_DIRECTORY bin)

## Set the output directories globally
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY})

# Create etc/config.ini in the build direcotry: it contains the paths to severals share/ directories
set(SHARE_DIR "${CMAKE_SOURCE_DIR}/share")
set(MESHES_DIR "${CMAKE_SOURCE_DIR}/share/mesh")
set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/share/shaders")
set(TEXTURES_DIR "${CMAKE_SOURCE_DIR}/share/textures")
configure_file(${CMAKE_SOURCE_DIR}/etc/config.ini.in "${CMAKE_BINARY_DIR}/etc/config.ini")

# Required packages
find_package(OpenGL REQUIRED)
find_package(assimp 4.0.0 EXACT REQUIRED)

if(${BUILD_EXAMPLES})
    add_subdirectory(app)
endif()

if(${BUILD_WITH_GLFW})
    find_package(glfw3 REQUIRED)

    list(APPEND HEADER_FILES
        src/glfw/GLFWApplication.h
        src/glfw/GLFWCameraController.h
        src/glfw/GLFWPickingController.h
    )
    list(APPEND SOURCE_FILES
        src/glfw/GLFWApplication.cpp
        src/glfw/GLFWCameraController.cpp
        src/glfw/GLFWPickingController.cpp
    )
endif()

#========== Creation of the library ==========#
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${PRIVATE_HEADER_FILES} ${PRIVATE_SOURCE_FILES} ${EXTLIBS_SOURCE_FILES} ${SHADER_FILES})

target_include_directories(${PROJECT_NAME}  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_include_directories(${PROJECT_NAME}  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/controller>)
target_include_directories(${PROJECT_NAME}  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/graph>)
target_include_directories(${PROJECT_NAME}  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/gui>)
target_include_directories(${PROJECT_NAME}  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/helper>)
target_include_directories(${PROJECT_NAME}  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/misc>)
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/opengl>)
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/statemachine>)
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${OPENGL_INCLUDE_DIR}>)
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extlibs/stb_image/include>)
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extlibs/glad/include>)
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIRS}>)

target_include_directories(${PROJECT_NAME}  PUBLIC $<INSTALL_INTERFACE:include/GLTK>)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} ${ASSIMP_LIBRARY_DIRS}/lib${ASSIMP_LIBRARIES}.a)

if(${BUILD_WITH_GLFW})
    target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/glfw>)
    target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${GLFW3_INCLUDE_DIR}>)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW3_LIBRARY})
endif()

#========= Install rules =========#

## Change default install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()

## install target binary
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Config
        LIBRARY
        INCLUDES DESTINATION "include"
        RUNTIME DESTINATION bin COMPONENT Runtime
        LIBRARY DESTINATION lib COMPONENT Runtime
        ARCHIVE DESTINATION lib COMPONENT Runtime
)

## install <project_name>Config.cmake
install(EXPORT ${PROJECT_NAME}Config DESTINATION lib/cmake)

## install header files
install(FILES ${HEADER_FILES} DESTINATION include/GLTK)

## install share/ directory
install(DIRECTORY share/ DESTINATION share)
