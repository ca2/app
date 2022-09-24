cmake_minimum_required(VERSION 3.16)
project(app_message_box CXX)


list(APPEND library_source
        _.cpp
        _.h
        #_factory.cpp
        ##_library.h
        application.cpp
        application.h
        framework.cpp
        framework.h
        main_window.cpp
        main_window.h)


add_library(${PROJECT_NAME} SHARED ${library_source})


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




list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(app_message_box PRIVATE _APP_MESSAGE_BOX_LIBRARY)


add_subdirectory(__implement)



