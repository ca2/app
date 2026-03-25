cmake_minimum_required(VERSION 3.16)
project(coding CXX)


list(APPEND library_source
        #build/_build.h
        #build/build.cpp
        #build/build.h
        _.cpp
        _.h
        _constant.h
        #_factory.cpp
        application.cpp
        application.h
   #        button_list_form_handler.cpp
   #    button_list_form_handler.h
        #distro__release_and_desktop_environment.cpp
        #3distro__release_and_desktop_environment.h
        code.cpp
        code.h
        code_application.cpp
        code_application.h
        #code_document.cpp
   #code_document.h
   #    code_frame.cpp
   #    code_frame.h
   #    code_impact.cpp
   #    code_impact.h
   #    code_install_form_handler.cpp
   #    code_install_form_handler.h
   #    code_main_frame.cpp
   #    code_main_frame.h
   #    code_option_form_handler.cpp
   #    code_option_form_handler.h
   #    code_tab_impact.cpp
   #    code_tab_impact.h
   #    document.cpp
   #    document.h
   #    frame.cpp
   #    frame.h
        framework.cpp
        framework.h
   #group.cpp
   #    group.h
   #    group_checkout_for_another_system.cpp
   #    group_checkout_for_another_system.h
   #    group_machine_box.cpp
   #    group_machine_box.h
   #    group_netnode.cpp
   #    group_netnode.h
   #    group_new_release_prefix.cpp
   #    group_new_release_prefix.h
   #    group_operating_system.cpp
   #    group_operating_system.h
   #impact.cpp
   #    impact.h
   #    impact_interface.cpp
   #    impact_interface.h
        install.cpp
        install.h
   #    integration.cpp
   #    integration.h
   #    integration_command.cpp
   #    integration_command.h
   #    integration_netnode.cpp
   #    integration_linux.cpp
   #    integration_linux.h
   #    integration_main.cpp
        #install_form_handler.cpp
        #install_form_handler.h
   #    install_impact_interface.cpp
   #    install_impact_interface.h
   #    install_log_interface.cpp
   #    install_log_interface.h
   #    integration.cpp
   #    integration.h
   #    integration_command.cpp
   #    integration_command.h
   #    integration_log_interface.h
        #item.cpp
        #item.h
   #    log_impact.cpp
   #    log_impact.h
   #    log_interface.cpp
   #    log_interface.h
   #    main_frame.cpp
   #    main_frame.h
   #    impact.cpp
   #    impact.h
        option.cpp
        option.h
   #    options_impact_handler.cpp
   #    options_impact_handler.h
        #summary.cpp
        #summary.h
   #    tab_impact.cpp
   #    tab_impact.h
        #task.cpp
        #task.h
        #task_group.cpp
        #task_group.h
        )

if(${FREEBSD})
    list(APPEND library_source
            install_freebsd.cpp
    )
endif()


if(${LINUX} OR ${FREEBSD})
    list(APPEND library_source
            install_posix.cpp
    )
endif()

if(${LINUX})
    list(APPEND library_source
            linux.cpp
            install_linux.cpp
            )
endif()

if(${WINDOWS})
    list(APPEND library_source
    integration_windows.cpp
integration_windows_build_tool.cpp)
    endif()



list(APPEND shared_library_references
        acme
        apex
        aqua
        aura
        axis
        berg
        dropbox
        )


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})
target_link_directories(static_${PROJECT_NAME} PRIVATE ${library_link_directories})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_compile_options(${PROJECT_NAME} PRIVATE "/bigobj")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${shared_library_references})


elseif(${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    #target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-rpath=\$ORIGIN")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${shared_library_references} ${global_library_references})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    #target_link_options(static_${PROJECT_NAME} PRIVATE -Wl,--whole-archive)


endif ()

if(${LINUX})
add_dependencies(${PROJECT_NAME} nano_archive_libarchive fs_folder_sync_dropbox)
endif()


target_compile_definitions(${PROJECT_NAME} PRIVATE _INTEGRATION_INTEGRATION_LIBRARY)


#add_subdirectory(__implement)

#
#add_executable(${PROJECT_NAME} application.cpp)
#
#
#if(${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})
##
##   add_custom_command(
##      COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
##      COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/matter.timestamp
##      OUTPUT ${PROJECT_BINARY_DIR}/matter.timestamp
##      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
##      BYPRODUCTS ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
##      DEPENDS application_matter.txt matter.txt _console_application_build_helper
##      VERBATIM
##      )
##
##   add_custom_target(${PROJECT_NAME}_matter
##      DEPENDS ${PROJECT_BINARY_DIR}/matter.timestamp
##   )
##
#list(APPEND executable_references ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o)
##
##   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)
##
#endif()
#
#
#
#list(APPEND executable_references
#   acme
#   apex
#   aqua
#   aura
#   axis
#   base
#   ${PROJECT_NAME})
#
#
#if (MSVC)
#
#   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
#   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
#   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
#   target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})
#
#elseif(${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})
#
#   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
#   #target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-rpath=\$ORIGIN")
#   target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})
#   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

#
#endif ()
#
#
#add_dependencies(${PROJECT_NAME} experience_tranquillum)
#add_dependencies(${PROJECT_NAME} ${default_draw2d})
#add_dependencies(${PROJECT_NAME} ${default_imaging})
#add_dependencies(${PROJECT_NAME} ${default_write_text})
#add_dependencies(${PROJECT_NAME} ${default_audio})
#add_dependencies(${PROJECT_NAME} audio_decode_wave)
#add_dependencies(${PROJECT_NAME} audio_decode_libmpg123)
#add_dependencies(${PROJECT_NAME} audio_resample_swresample)
#add_dependencies(${PROJECT_NAME} text_to_speech_google)
#add_dependencies(${PROJECT_NAME} database_sqlite3)
#add_dependencies(${PROJECT_NAME} regular_expression_pcre2)
#add_dependencies(${PROJECT_NAME} crypto_openssl)
#
#
#list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
#list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
#list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
#
#target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
#
#
#target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})
#
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#
#
#
#
#
##
