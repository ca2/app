cmake_minimum_required(VERSION 3.17)
project(app_shader CXX)


list(APPEND library_source
   _.cpp
    _.h
    _user.h
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


add_executable(app_shader ${library_source})

target_precompile_headers(app_shader PRIVATE framework.h)

set_target_properties(app_shader PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(app_shader PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_shader PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_shader PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_shader PRIVATE ${library_references})

elseif(LINUX)
    #target_link_options(app_shader PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_shader PRIVATE ${library_references})
    target_link_options(app_shader PRIVATE -Wl,-z,defs)

endif()

add_dependencies(app_shader ${app_common_dependencies})
add_dependencies(app_shader ${default_gpu})
add_dependencies(app_shader ${default_draw2d})


target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_shader PRIVATE _APP_SHADER_LIBRARY)



