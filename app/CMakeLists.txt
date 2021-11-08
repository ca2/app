cmake_minimum_required(VERSION 3.17)
project(app_app CXX)


list(APPEND library_source
        _.cpp
        _.h
        _user.h
        application.cpp
        application.h
        framework.cpp
        framework.h
        main_window.cpp
        main_window.h)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   )


add_library(app_app SHARED ${library_source})

target_precompile_headers(app_app PRIVATE framework.h)

set_target_properties(app_app PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)

    target_compile_options(app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_app PRIVATE ${library_references})

elseif(LINUX)

    #target_link_options(app_app PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_app PRIVATE ${library_references})
    target_link_options(app_app PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})

endif()

add_dependencies(app_app ${app_common_dependencies})
add_dependencies(app_app apex_${PLATFORM_NAME})
add_dependencies(app_app ${default_node})
add_dependencies(app_app ${default_draw2d})


target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_app PRIVATE _APP_APP_LIBRARY)



add_executable(_app_app _app_app.cpp)




list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_app
   )



if (MSVC)

    target_compile_options(_app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(_app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(_app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(_app_app PRIVATE ${executable_references})

elseif (LINUX)

    target_compile_options(_app_app PRIVATE -fpermissive)
    target_link_libraries(_app_app PRIVATE ${executable_references})
    target_link_options(_app_app PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_app_app ${app_common_dependencies})
add_dependencies(_app_app ${default_draw2d})


target_include_directories(_app_app PRIVATE ${library_include_directories})

target_link_directories(_app_app PRIVATE ${library_link_directories})

set_target_properties(_app_app PROPERTIES LINKER_LANGUAGE CXX)



