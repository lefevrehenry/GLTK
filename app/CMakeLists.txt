cmake_minimum_required(VERSION 3.2)
project(app)

set(EXECUTABLE_FILES
#    deferredShading
    environmentMapping
#    normalMapping
    picking
#    shadertoy
#    prog
)

#find_package(Threads)
#find_package(glfw3 CONFIG REQUIRED)

macro(create_executable target_name)
    message(STATUS "${target_name}")

    add_executable(${target_name} ${target_name}.cpp)
    target_link_libraries(${target_name} PRIVATE GLTK)# Threads::Threads)

    set_target_properties(${target_name} PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")

    ## install binary
    install(TARGETS ${target_name}
            RUNTIME DESTINATION bin COMPONENT Runtime
            LIBRARY DESTINATION lib COMPONENT Runtime
            ARCHIVE DESTINATION lib COMPONENT Runtime
    )
endmacro()

foreach(exec ${EXECUTABLE_FILES})
    create_executable(${exec})
endforeach()
