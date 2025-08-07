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
add_library(static_${PROJECT_NAME} STATIC ${library_source})




if(${LINUX} OR ${__BSD__})


    add_custom_command(
       OUTPUT ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
       COMMAND ${APPLICATION_BUILD_HELPER_BINARY} --prepare-application ${PROJECT_SOURCE_DIR}
       COMMENT "Generating ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o"
    )

    target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

endif()




list(APPEND library_references
   acme
   apex
   aqua
   aura
   app_app
   )


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(app_message_box PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(app_message_box PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_message_box PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_message_box PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_message_box PRIVATE ${library_references} ${global_library_references})
elseif(${LINUX})

    #if(GTK_BASED_DESKTOP)
    #    add_dependencies(app_message_box node_gnome windowing_x11)
    #endif()
    #if(KDE_DESKTOP)
    #   add_dependencies(app_message_box node_kde windowing_xcb)
    #endif()

    target_link_libraries(app_message_box PRIVATE ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message(STATUS "(F) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
endif()


add_dependencies(${PROJECT_NAME} crypto_openssl)
add_dependencies(${PROJECT_NAME} folder_zip)
add_dependencies(${PROJECT_NAME} ${default_write_text})

#if(${LINUX})
#    if(${WITH_X11})
#        add_dependencies(${PROJECT_NAME} nano_user_x11)
#    endif()
#endif()



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)


add_subdirectory(__implement)



