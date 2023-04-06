cmake_minimum_required(VERSION 3.16)
project(app_app CXX)


list(APPEND library_source
        _.cpp
        _.h
        ##_library.h
        _factory.h
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


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(app_app PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)

    target_compile_options(app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_app PRIVATE ${library_references})

elseif(LINUX)

    #target_link_options(app_app PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_app PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})

endif()

add_dependencies(app_app apex_${OPERATING_SYSTEM_NAME})
add_dependencies(app_app ${default_node})
add_dependencies(app_app ${default_draw2d})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


add_subdirectory(__implement)

