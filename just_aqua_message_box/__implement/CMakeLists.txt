cmake_minimum_required(VERSION 3.16)
project(_app_just_aqua_message_box CXX)



list(APPEND application_source application_main.cpp)


if(MSVC)
    list(APPEND application_source ../deployment.rc main.rc)
endif()


add_executable(${PROJECT_NAME} ${application_source})




list(APPEND executable_references
        acme
        apex
        aqua
        app_just_aqua_message_box
        )


if(${LINUX} OR ${__BSD__})


   add_custom_command(
      OUTPUT ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o
      COMMAND application_build_helper --prepare-application ${PROJECT_SOURCE_DIR}
      COMMENT "Generating ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o"
   )

   target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o)

endif()


if (MSVC)


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})


elseif(${LINUX} OR ${__BSD__})


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)


endif ()


add_dependencies(${PROJECT_NAME} ${apex_libraries})
add_dependencies(${PROJECT_NAME} ${innate_ui_libraries})


list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${executable_include_directories})


target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)



