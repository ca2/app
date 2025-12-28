cmake_minimum_required(VERSION 3.16)
project(_app_app CXX)


list(APPEND application_source main.cpp)


if(MSVC)
    list(APPEND application_source ../deployment.rc main.rc)
endif()


add_executable(${PROJECT_NAME} ${application_source})
#add_library(applib${PROJECT_NAME} SHARED ${application_source})


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


if(${WIN32})

    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})

elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(${PROJECT_NAME} ${app_common_dependencies})
add_dependencies(${PROJECT_NAME} ${default_draw2d})
add_dependencies(${PROJECT_NAME} ${default_imaging})
add_dependencies(${PROJECT_NAME} ${default_node})
add_dependencies(${PROJECT_NAME} crypto_openssl)
add_dependencies(${PROJECT_NAME} folder_zip)
add_dependencies(${PROJECT_NAME} networking_bsd)


list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${executable_include_directories})


target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)



