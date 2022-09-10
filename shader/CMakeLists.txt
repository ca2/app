cmake_minimum_required(VERSION 3.16)
project(app_shader CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   #_factory.cpp
   application.cpp
   application.h
   framework.h
   render.cpp
   render.h
   main_window.cpp
   main_window.h)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   )


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})

elseif(LINUX OR FREEBSD)

   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)

endif ()


target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _APP_SIMPLE_DRAWING_LIBRARY)


#add_executable(_${PROJECT_NAME} _main.cpp)
add_executable(_${PROJECT_NAME} _main.cpp)


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   ${PROJECT_NAME}
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


   target_compile_options(_${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_${PROJECT_NAME} PRIVATE ${executable_references})


elseif(LINUX OR FREEBSD)


   target_compile_options(_${PROJECT_NAME} PRIVATE -fpermissive)
   target_link_libraries(_${PROJECT_NAME} PRIVATE ${executable_references})
   target_link_options(_${PROJECT_NAME} PRIVATE -Wl,-z,defs)


endif ()



add_dependencies(_${PROJECT_NAME} ${default_draw2d})
add_dependencies(_${PROJECT_NAME} ${default_write_text})
add_dependencies(_${PROJECT_NAME} ${app_common_dependencies})
add_dependencies(_${PROJECT_NAME} crypto_openssl)
add_dependencies(_${PROJECT_NAME} folder_zip)
add_dependencies(_${PROJECT_NAME} gpu_opengl)



target_include_directories(_${PROJECT_NAME} PRIVATE ${library_include_directories})

target_link_directories(_${PROJECT_NAME} PRIVATE ${library_link_directories})

set_target_properties(_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)



