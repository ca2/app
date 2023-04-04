cmake_minimum_required(VERSION 3.16)
project(app_integration CXX)


list(APPEND library_source
        _.cpp
        _.h
        ##_library.h
        #_factory.cpp
        application.cpp
        application.h
        document.cpp
        document.h
        framework.cpp
        framework.h
        frame.cpp
        frame.h
        impact.cpp
        impact.h
        main_frame.cpp
        main_frame.h
        render.cpp
        render.h
        render_1through3.cpp
        render_arcs.cpp
        render_box.cpp
        render_circle_path.cpp
        tab_impact.cpp
        tab_impact.h
        )


add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(app_integration PRIVATE framework.h)

set_target_properties(app_integration PROPERTIES LINKER_LANGUAGE CXX)


list(APPEND library_references
        acme
        apex
        aqua
        aura
        axis
        base
        )


if (MSVC)

    target_compile_options(app_integration PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_integration PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_integration PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_integration PRIVATE ${library_references})

elseif (LINUX OR FREEBSD)

    target_compile_options(app_integration PRIVATE -fpermissive)
    #target_link_options(app_integration PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_integration PRIVATE ${library_references})
    target_link_options(app_integration PRIVATE -Wl,-z,defs)

endif ()


target_link_directories(app_integration PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(app_integration PRIVATE _APP_INTEGRATION_LIBRARY)


add_subdirectory(__implement)

