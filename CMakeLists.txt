CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(GLTK)

#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g")

set(HEADER_FILES
    controller/Controller.h

    graph/Node.h
    graph/SceneGraph.h
    graph/Selectable.h
    graph/Visitor.h

    gui/SceneView.h

    helper/FileRepository.h
    helper/Message.h

    misc/Application.h
    misc/Camera.h
    misc/Light.h
    misc/Material.h
    misc/Rect.h
    misc/Transform.h

    opengl/Data.h
    opengl/Framebuffer.h
    opengl/Mesh.h
    opengl/Shader.h
    opengl/ShaderProgram.h
    opengl/Texture.h
    opengl/VisualManager.h
    opengl/VisualModel.h
    opengl/VisualOption.h

    statemachine/OpenGLAttribute.h
    statemachine/OpenGLStateMachine.h

    gltk.h
)

set(SOURCE_FILES
    controller/Controller.cpp

    graph/Node.cpp
    graph/SceneGraph.cpp
    graph/Selectable.cpp
    graph/Visitor.cpp

    gui/SceneView.cpp

    helper/FileRepository.cpp
    helper/Message.cpp

    misc/Application.cpp
    misc/Camera.cpp
    misc/Light.cpp
    misc/Material.cpp
    misc/Rect.cpp
    misc/Transform.cpp

    opengl/Data.cpp
    opengl/Framebuffer.cpp
    opengl/Mesh.cpp
    opengl/Shader.cpp
    opengl/ShaderProgram.cpp
    opengl/Texture.cpp
    opengl/VisualManager.cpp
    opengl/VisualModel.cpp
    opengl/VisualOption.cpp

    statemachine/OpenGLAttribute.cpp
    statemachine/OpenGLAttribute.inl
    statemachine/OpenGLStateMachine.cpp
    statemachine/OpenGLStateMachine.inl

    gltk.cpp
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
        glfw/GLFWApplication.h
        glfw/GLFWCameraController.h
        glfw/GLFWPickingController.h
    )
    set(SOURCE_FILES
        ${SOURCE_FILES}
        glfw/GLFWApplication.cpp
        glfw/GLFWCameraController.cpp
        glfw/GLFWPickingController.cpp
    )
endif()

set(STB_IMAGE_INCLUDE_DIR
    extlibs/stb_image/include
)

#========== Creation of the library ==========#
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${STB_IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES})

if(${BUILD_WITH_GLFW})
    target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW3_INCLUDE_DIR})
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
        target_include_directories(${PROJECT_NAME} PUBLIC ${${NAME}_PATH}/include)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${${NAME}_LIBRARY})
    endif()
endmacro()

link_with_local_lib(extlibs/glew GLEW)
link_with_local_lib(extlibs/assimp assimp)


#========= Install rules =========#

## Change default install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()

install(FILES ${HEADER_FILES} DESTINATION include/GLTK)
install(FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} DESTINATION lib)
