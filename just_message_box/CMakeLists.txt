cmake_minimum_required(VERSION 3.16)
project(app_just_message_box CXX)


list(APPEND library_source
    _.cpp
    _.h
    application.cpp
    application.h
    framework.cpp
    framework.h)


list(APPEND library_references
    acme
    apex
    aqua
    aura
    )



add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(app_just_message_box PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(app_just_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_just_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_just_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_just_message_box PRIVATE acme apex aqua aura)
    add_dependencies(app_just_message_box draw2d_gdiplus)


elseif(${LINUX})

    target_link_libraries(app_just_message_box PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif()




list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(app_just_message_box PRIVATE _APP_JUST_MESSAGE_BOX_LIBRARY)


add_subdirectory(__implement)


