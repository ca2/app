cmake_minimum_required(VERSION 3.17)
project(app_message_box CXX)


list(APPEND library_source
        _.cpp
        _.h
        _user.h
        application.cpp
        application.h
        framework.cpp
        framework.h
        window.cpp
        window.h)


add_executable(app_message_box ${library_source})

target_precompile_headers(app_message_box PRIVATE framework.h)

set_target_properties(app_message_box PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(app_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_message_box PRIVATE acme apex aqua aura)
elseif(LINUX)

    #if(LINUX_GNOME)
    #    add_dependencies(app_message_box node_gnome windowing_x11)
    #endif()
    #if(LINUX_KDE)
    #   add_dependencies(app_message_box node_kde windowing_xcb)
    #endif()

    #target_link_options(app_message_box PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_message_box PRIVATE acme apex aqua aura)
    target_link_options(app_message_box PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


add_dependencies(app_message_box ${app_common_dependencies})
add_dependencies(app_message_box apex_${PLATFORM_NAME})
add_dependencies(app_message_box ${default_node})
add_dependencies(app_message_box ${default_draw2d})
add_dependencies(app_message_box ${default_write_text})


target_include_directories(app_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_message_box PRIVATE _APP_MESSAGE_BOX_LIBRARY)

add_executable(_app_message_box _main.cpp)


if (MSVC)

    target_compile_options(_app_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(_app_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(_app_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(_app_message_box PRIVATE ${app_core_hellomultiverse_references} app_core_hellomultiverse)

elseif (LINUX)

    target_compile_options(_app_message_box PRIVATE -fpermissive)
    #target_link_options(_app_message_box PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(_app_message_box PRIVATE ${app_core_hellomultiverse_references} app_core_hellomultiverse)
    target_link_options(_app_message_box PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_app_message_box ${app_common_dependencies})
add_dependencies(_app_message_box ${default_draw2d})


target_include_directories(_app_message_box PRIVATE ${library_include_directories})

target_link_directories(_app_message_box PRIVATE ${library_link_directories})

target_link_libraries(_app_message_box PRIVATE acme apex aqua aura app_app)

set_target_properties(_app_message_box PROPERTIES LINKER_LANGUAGE CXX)



