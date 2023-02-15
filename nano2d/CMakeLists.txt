cmake_minimum_required(VERSION 3.16)
project(nano2d CXX)


list(APPEND library_source
        color.cpp
        color.h
        context.cpp
        context.h
        draw2d_context.cpp
        draw2d_context.h
        font_sink.cpp
        font_sink.h
        _.cpp
        _.h
        )


list(APPEND library_references
        acme
        apex
        aqua
        aura
        )


add_library(${PROJECT_NAME} SHARED ${library_source} _function.h _constant.h)


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
elseif (LINUX OR FREEBSD)
    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    #target_link_options(${PROJECT_NAME}  PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
endif ()


add_dependencies(${PROJECT_NAME} experience_core)
add_dependencies(${PROJECT_NAME} ${default_draw2d})
add_dependencies(${PROJECT_NAME} ${default_write_text})
add_dependencies(${PROJECT_NAME} database_sqlite3)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _NANOUI_LIBRARY)

