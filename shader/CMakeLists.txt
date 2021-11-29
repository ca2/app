cmake_minimum_required(VERSION 3.17)
project(app_shader CXX)


list(APPEND library_source
   _.cpp
   _.h
   _app_shader.h
   application.cpp
   application.h
   framework.h
   render.cpp
   render.h
   main_window.cpp
   main_window.h)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   )


add_library(app_shader SHARED ${library_source})

target_precompile_headers(app_shader PRIVATE framework.h)

set_target_properties(app_shader PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

   target_compile_options(app_shader PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(app_shader PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_shader PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_shader PRIVATE ${library_references})

elseif(LINUX OR FREEBSD)

   target_compile_options(app_shader PRIVATE -fpermissive)
   #target_link_options(app_shader PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(app_shader PRIVATE ${library_references})
   target_link_options(app_shader PRIVATE -Wl,-z,defs)

endif ()


target_link_directories(app_shader PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(app_shader PRIVATE ${library_include_directories})


target_compile_definitions(app_shader PRIVATE _APP_SIMPLE_DRAWING_LIBRARY)


add_executable(_app_shader _main.cpp)


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_shader
   )


if(LINUX OR FREEBSD)


    add_custom_command(
       TARGET ${PROJECT_NAME}
       POST_BUILD
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
       COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
       COMMAND ${APPLICATION_BUILD_RESOURCE_OBJECT_PRE}${PROJECT_BINARY_DIR}${APPLICATION_BUILD_RESOURCE_OBJECT_POS}
       VERBATIM
    )


    list(APPEND executable_references ${PROJECT_BINARY_DIR}/_matter.zip.o)


endif()



if (MSVC)

   target_compile_options(_app_shader PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_app_shader PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_app_shader PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_app_shader PRIVATE ${executable_references})

elseif(LINUX OR FREEBSD)

   target_compile_options(_app_shader PRIVATE -fpermissive)
   #target_link_options(_app_shader PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(_app_shader PRIVATE ${executable_references})
   target_link_options(_app_shader PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_app_shader ${default_draw2d})
add_dependencies(_app_shader ${app_common_dependencies})
add_dependencies(_app_shader gpu_opengl)


target_include_directories(_app_shader PRIVATE ${library_include_directories})

target_link_directories(_app_shader PRIVATE ${library_link_directories})

target_link_libraries(_app_shader PRIVATE acme apex app_shader)

set_target_properties(_app_shader PROPERTIES LINKER_LANGUAGE CXX)



