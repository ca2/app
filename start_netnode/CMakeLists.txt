cmake_minimum_required(VERSION 3.16)
project(app_app CXX)


list(APPEND library_source
        _.cpp
        _.h
        ${PROJECT_NAME}.h
        #_factory.cpp
        _factory.h
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

set_target_properties(app_app PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)

    target_compile_options(app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_app PRIVATE ${library_references} ${global_library_references})

elseif(${LINUX})

    target_link_libraries(app_app PRIVATE ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message(STATUS "(I) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})

endif()

add_dependencies(app_app apex_${OPERATING_SYSTEM_NAME})
add_dependencies(app_app ${default_node})
add_dependencies(app_app ${default_draw2d})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



add_subdirectory(__implement)



list(APPEND application_source application_main.cpp)


if(MSVC)
    list(APPEND application_source ../deployment.rc main.rc)
endif()


add_executable(${PROJECT_NAME} ${application_source})




list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_app
   )


#if(${LINUX} OR ${__BSD__})


#   add_custom_command(
#      OUTPUT ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o
#      COMMAND ${APPLICATION_BUILD_HELPER_BINARY} --prepare-application ${PROJECT_SOURCE_DIR}
#      COMMENT "Generating ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o"
#   )

#   target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o)

#endif()


if (MSVC)

    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})

elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


add_dependencies(${PROJECT_NAME} ${default_draw2d})
add_dependencies(${PROJECT_NAME} ${default_node})
add_dependencies(${PROJECT_NAME} crypto_openssl)
add_dependencies(${PROJECT_NAME} folder_zip)



target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)



