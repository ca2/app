cmake_minimum_required(VERSION 3.17)
project(app_message_box CXX)


list(APPEND library_source
        _.cpp
        _.h
        _app_message_box.h
        application.cpp
        application.h
        framework.cpp
        framework.h
        main_window.cpp
        main_window.h)


add_library(app_message_box SHARED ${library_source})


list(APPEND library_references
   acme
   apex
   aqua
   aura
   app_app
   )


target_precompile_headers(app_message_box PRIVATE framework.h)

set_target_properties(app_message_box PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(app_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_message_box PRIVATE ${library_references})
elseif(LINUX)

    #if(GNOME_DESKTOP)
    #    add_dependencies(app_message_box node_gnome windowing_x11)
    #endif()
    #if(KDE_DESKTOP)
    #   add_dependencies(app_message_box node_kde windowing_xcb)
    #endif()

    #target_link_options(app_message_box PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_message_box PRIVATE ${library_references})
    target_link_options(app_message_box PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()




target_include_directories(app_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_message_box PRIVATE _APP_MESSAGE_BOX_LIBRARY)

add_executable(_app_message_box _main.cpp)


add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/_matter.zip.o
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
   COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
   COMMAND ld -r -b binary -o ${PROJECT_BINARY_DIR}/_matter.zip.o _matter.zip
   DEPENDS deps.txt matter.txt
)

target_sources(_${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR}/_matter.zip.o)



list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_message_box
   )


if (MSVC)

    target_compile_options(_app_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(_app_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(_app_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(_app_message_box PRIVATE ${executable_references})

elseif(LINUX OR FREEBSD)

    target_compile_options(_app_message_box PRIVATE -fpermissive)
    target_link_libraries(_app_message_box PRIVATE ${executable_references})
    target_link_options(_app_message_box PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_app_message_box ${app_common_dependencies})
add_dependencies(app_message_box apex_${PLATFORM_NAME})
add_dependencies(app_message_box ${default_node})
add_dependencies(_app_message_box ${default_draw2d})
add_dependencies(_app_message_box ${default_write_text})


target_include_directories(_app_message_box PRIVATE ${library_include_directories})

target_link_directories(_app_message_box PRIVATE ${library_link_directories})

set_target_properties(_app_message_box PROPERTIES LINKER_LANGUAGE CXX)



