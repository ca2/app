cmake_minimum_required(VERSION 3.16)
project(_app_app CXX)


list(APPEND application_source main.cpp)


if(WIN32)
    list(APPEND application_source ../deployment.rc main.rc)
endif()


add_executable(${PROJECT_NAME} ${application_source})

if(__HAIKU__)
   haiku_set_application_icon(${PROJECT_NAME}
      "app/app"
      "../../_matter/app/_std/_std/main/icon.png")
endif()
#add_library(applib${PROJECT_NAME} SHARED ${application_source})


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_app
   )


if(${LINUX} OR ${__BSD__} OR ${__SUNOS__} OR ${__HAIKU__})

   target_sources(${PROJECT_NAME} PRIVATE .link_object/_matter.zip.o)

endif()


if(${WIN32})





   if(MSVC)
      target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
      target_link_options(${PROJECT_NAME} PRIVATE "/bigobj")
      #target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
      #target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   else()
      target_link_options(${PROJECT_NAME} PRIVATE "-mwindows")
      if(MINGW)
         target_link_options(${PROJECT_NAME} PRIVATE "-municode")
      endif()
      #target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   endif()



    target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})

elseif (${LINUX} OR ${__BSD__} OR ${__ANDROID__} OR ${__SUNOS__} OR ${__HAIKU__})

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




# Deploy the MinGW ports alongside the executable so ReactOS can resolve them.
if(MINGW AND CMAKE_SIZEOF_VOID_P EQUAL 4 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   foreach(port_runtime sqlite unac idn iconv zlib archive freetype cairo pixman png libcrypto libssl)
      if(TARGET ${port_runtime})
         add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "$<TARGET_FILE:${port_runtime}>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            VERBATIM)
      endif()
   endforeach()
endif()

option(CA2_STARTUP_TRACE "Write startup stages to ca2-startup.log beside the executable" OFF)
option(CA2_ATTACH_PARENT_CONSOLE "Attach GUI startup to the invoking console when available" OFF)
if(WIN32)
   target_compile_definitions(${PROJECT_NAME} PRIVATE
      CA2_STARTUP_TRACE=$<BOOL:${CA2_STARTUP_TRACE}>
      CA2_ATTACH_PARENT_CONSOLE=$<BOOL:${CA2_ATTACH_PARENT_CONSOLE}>)
endif()
