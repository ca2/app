cmake_minimum_required(VERSION 3.16)
project(_app_shader CXX)


add_executable(${PROJECT_NAME} application.cpp)


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   app_shader
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
list(APPEND executable_references ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o)
#
#   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)
#
endif()


if (MSVC)


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})


elseif(LINUX OR FREEBSD)


   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)


endif ()



add_dependencies(${PROJECT_NAME} ${default_draw2d})
add_dependencies(${PROJECT_NAME} ${default_write_text})
add_dependencies(${PROJECT_NAME} ${app_common_dependencies})
add_dependencies(${PROJECT_NAME} crypto_openssl)
add_dependencies(${PROJECT_NAME} folder_zip)
add_dependencies(${PROJECT_NAME} gpu_opengl)



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)



