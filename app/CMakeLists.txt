cmake_minimum_required(VERSION 3.16)
project(app_app CXX)


list(APPEND library_source
        _.cpp
        _.h
        _app_app.h
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


add_library(app_app SHARED ${library_source})

target_precompile_headers(app_app PRIVATE framework.h)

set_target_properties(app_app PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)

    target_compile_options(app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_app PRIVATE ${library_references})

elseif(LINUX)

    #target_link_options(app_app PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(app_app PRIVATE ${library_references})
    target_link_options(app_app PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})

endif()

add_dependencies(app_app ${app_common_dependencies})
add_dependencies(app_app apex_${OPERATING_SYSTEM_NAME})
add_dependencies(app_app ${default_node})
add_dependencies(app_app ${default_draw2d})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(_${PROJECT_NAME} _main.cpp)


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_app
   )


if(LINUX OR FREEBSD)
#
#   add_custom_command(
#      COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
#      COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/matter.timestamp
#      OUTPUT ${PROJECT_BINARY_DIR}/matter.timestamp
#      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#      BYPRODUCTS ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
#      DEPENDS application_matter.txt matter.txt _console_application_build_helper
#      VERBATIM
#      )
#
#   add_custom_target(${PROJECT_NAME}_matter
#      DEPENDS ${PROJECT_BINARY_DIR}/matter.timestamp
#   )
#
list(APPEND executable_references ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)
#
#   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)
#
endif()


if (MSVC)

    target_compile_options(_app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(_app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(_app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(_app_app PRIVATE ${executable_references})

elseif(LINUX OR FREEBSD)

    target_compile_options(_app_app PRIVATE -fpermissive)
    target_link_libraries(_app_app PRIVATE ${executable_references})
    target_link_options(_app_app PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_app_app ${app_common_dependencies})
add_dependencies(_app_app ${default_draw2d})
add_dependencies(_app_app crypto_openssl)
add_dependencies(_app_app folder_zip)


target_include_directories(_app_app PRIVATE ${library_include_directories})

target_link_directories(_app_app PRIVATE ${library_link_directories})

set_target_properties(_app_app PROPERTIES LINKER_LANGUAGE CXX)



