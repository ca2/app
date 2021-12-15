cmake_minimum_required(VERSION 3.17)
project(app_just_message_box CXX)


list(APPEND library_source
        _.cpp
        _.h
        _user.h
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



add_library(app_just_message_box ${library_source})


target_precompile_headers(app_just_message_box PRIVATE framework.h)


set_target_properties(app_just_message_box PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(app_just_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_just_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_just_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_just_message_box PRIVATE acme apex aqua aura)
    add_dependencies(app_just_message_box draw2d_gdiplus)


elseif(LINUX)

    #if(GNOME_DESKTOP)
    #    add_dependencies(app_just_message_box node_gnome windowing_x11)
    #endif()
    #if(KDE_DESKTOP)
    #   add_dependencies(app_just_message_box node_kde windowing_xcb)
    #endif()

    #target_link_options(app_just_message_box PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_just_message_box PRIVATE ${library_references})
    target_link_options(app_just_message_box PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
    add_dependencies(app_just_message_box draw2d_cairo)


endif()


add_dependencies(app_just_message_box ${app_common_dependencies})
add_dependencies(app_just_message_box ${default_write_text})
add_dependencies(app_just_message_box ${default_draw2d})


target_include_directories(app_just_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_just_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_just_message_box PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_just_message_box PRIVATE _app_just_message_box_LIBRARY)


add_executable(_app_just_message_box _app_just_message_box.cpp)


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_just_message_box
   )


if(LINUX OR FREEBSD)

   add_custom_command(
      COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
      COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/matter.timestamp
      OUTPUT ${PROJECT_BINARY_DIR}/matter.timestamp
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      BYPRODUCTS ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o 
      DEPENDS application_matter.txt deps.txt matter.txt _console_application_build_helper
      VERBATIM
      )

   add_custom_target(${PROJECT_NAME}_matter
      DEPENDS ${PROJECT_BINARY_DIR}/matter.timestamp
   )

   list(APPEND executable_references ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)

endif()


if (MSVC)


    target_compile_options(_app_just_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(_app_just_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(_app_just_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(_app_just_message_box PRIVATE ${executable_references})


elseif(LINUX OR FREEBSD)


    target_compile_options(_app_just_message_box PRIVATE -fpermissive)
    target_link_libraries(_app_just_message_box PRIVATE ${executable_references})
    target_link_options(_app_just_message_box PRIVATE -Wl,-z,defs)


endif ()


add_dependencies(_app_just_message_box ${app_common_dependencies})
add_dependencies(_app_just_message_box ${default_draw2d})


target_include_directories(_app_just_message_box PRIVATE ${library_include_directories})

target_link_directories(_app_just_message_box PRIVATE ${library_link_directories})

target_link_libraries(_app_just_message_box PRIVATE acme apex aqua aura app_app)

set_target_properties(_app_just_message_box PROPERTIES LINKER_LANGUAGE CXX)



