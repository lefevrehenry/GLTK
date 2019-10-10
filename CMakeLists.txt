CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(GLTK)

#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g")

set(HEADER_FILES
    src/controller/Controller.h

    src/graph/BoundingBoxVisitor.h
    src/graph/DrawVisitor.h
    src/graph/DrawWithSelectionVisitor.h
    src/graph/FetchVisualModelVisitor.h
    src/graph/Node.h
    src/graph/PickingVisitor.h
    src/graph/SceneGraph.h
    src/graph/ShaderVisitor.h
    src/graph/Visitor.h

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
    src/graph/DrawVisitor.cpp
    src/graph/DrawWithSelectionVisitor.cpp
    src/graph/FetchVisualModelVisitor.cpp
    src/graph/Node.cpp
    src/graph/PickingVisitor.cpp
    src/graph/SceneGraph.cpp
    src/graph/ShaderVisitor.cpp
    src/graph/Visitor.cpp

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
    src/opengl/CubeMapTexture.h
    src/opengl/Data.h
    src/opengl/Framebuffer.h
    src/opengl/Mesh.h
    src/opengl/Shader.h
    src/opengl/ShaderProgram.h
    src/opengl/Texture.h
    src/opengl/Texture2D.h
    src/opengl/VisualManager.h
    src/opengl/VisualModel.h
    src/opengl/VisualOption.h

    src/statemachine/OpenGLAttribute.h
    src/statemachine/OpenGLStateMachine.h
)

set(PRIVATE_SOURCE_FILES
    src/opengl/CubeMapTexture.cpp
    src/opengl/Data.cpp
    src/opengl/Framebuffer.cpp
    src/opengl/Mesh.cpp
    src/opengl/Shader.cpp
    src/opengl/ShaderProgram.cpp
    src/opengl/Texture.cpp
    src/opengl/Texture2D.cpp
    src/opengl/VisualManager.cpp
    src/opengl/VisualModel.cpp
    src/opengl/VisualOption.cpp

    src/statemachine/OpenGLAttribute.cpp
    src/statemachine/OpenGLAttribute.inl
    src/statemachine/OpenGLStateMachine.cpp
    src/statemachine/OpenGLStateMachine.inl
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

if(${BUILD_EXAMPLES})
    add_subdirectory(app)
endif()

if(${BUILD_WITH_GLFW})
    find_package(glfw3 REQUIRED)

    set(HEADER_FILES
        ${HEADER_FILES}
        src/glfw/GLFWApplication.h
        src/glfw/GLFWCameraController.h
        src/glfw/GLFWPickingController.h
    )
    set(SOURCE_FILES
        ${SOURCE_FILES}
        src/glfw/GLFWApplication.cpp
        src/glfw/GLFWCameraController.cpp
        src/glfw/GLFWPickingController.cpp
    )
endif()

set(STB_IMAGE_INCLUDE_DIR
    extlibs/stb_image/include
)

#========== Creation of the library ==========#
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${PRIVATE_HEADER_FILES} ${PRIVATE_SOURCE_FILES} ${SHADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/controller>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/graph>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/gui>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/helper>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/misc>)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/statemachine)

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${STB_IMAGE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

if(${BUILD_WITH_GLFW})
    target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/glfw>)
    target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${GLFW3_INCLUDE_DIR}>)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW3_LIBRARY})
endif()

#========= Linking with local library =========#
macro(link_with_local_lib LOCAL_PATH NAME)
    set(${NAME}_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${LOCAL_PATH})

    find_library(${NAME}_LIBRARY
        NAME ${NAME}
        NO_DEFAULT_PATH
        PATHS ${${NAME}_PATH}/lib
    )

    if(${NAME})
        message(FATAL_ERROR "${NAME}_LIBRARY library not found !")
    else()
        target_include_directories(${PROJECT_NAME} PRIVATE ${${NAME}_PATH}/include)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${${NAME}_LIBRARY})
    endif()
endmacro()

link_with_local_lib(extlibs/glew GLEW)
link_with_local_lib(extlibs/assimp assimp)


#========= Install rules =========#

## Change default install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()

## install target binary
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Config
        RUNTIME DESTINATION bin COMPONENT Runtime
        LIBRARY DESTINATION lib COMPONENT Runtime
        ARCHIVE DESTINATION lib COMPONENT Runtime
)

## install <project_name>Targets.cmake
install(EXPORT ${PROJECT_NAME}Config DESTINATION lib/cmake)

## install header files
install(FILES ${HEADER_FILES} DESTINATION include/GLTK)
