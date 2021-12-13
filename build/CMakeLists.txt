cmake_minimum_required(VERSION 3.17)
project(app_core_build CXX)


list(APPEND library_source
   build/_build.h
   build/build.cpp
   build/build.h
   _.cpp
   _.h
   application.cpp
   application.h
   document.cpp
   document.h
   frame.cpp
   frame.h
   framework.cpp
   framework.h
   impact.cpp
   impact.h
   main_frame.cpp
   main_frame.h
   main_impact.cpp
   main_impact.h
   pane_view.cpp
   pane_view.h
   impact.cpp
   impact.h
   )


if(LINUX)

   list(APPEND library_source
      build/linux.cpp
      build/linux.h)

endif()


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
   core
   )


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


add_library(app_core_build SHARED ${library_source})


target_include_directories(app_core_build PRIVATE ${library_include_directories})


target_link_directories(app_core_build PRIVATE ${library_link_directories})


target_precompile_headers(app_core_build PRIVATE framework.h)


set_target_properties(app_core_build PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(app_core_build PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_compile_options(app_core_build PRIVATE "/bigobj")
   target_link_options(app_core_build PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_core_build PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_core_build PRIVATE ${library_references})
elseif(LINUX OR FREEBSD)
   target_compile_options(app_core_build PRIVATE -fpermissive)
   #target_link_options(app_core_build PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(app_core_build PRIVATE ${library_references})
   target_link_options(app_core_build PRIVATE -Wl,-z,defs)
endif ()


target_compile_definitions(app_core_build PRIVATE _APP_CORE_BUILD_LIBRARY)


add_executable(_${PROJECT_NAME} _${PROJECT_NAME}.cpp)


if(LINUX OR FREEBSD)

   add_custom_command(
      COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
      COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/matter.timestamp
      OUTPUT ${CMAKE_BINARY_DIR}/matter.timestamp
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      BYPRODUCTS ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o 
      DEPENDS deps.txt matter.txt _console_application_build_helper
      VERBATIM
      )

   add_custom_target(${PROJECT_NAME}_matter
      DEPENDS ${CMAKE_BINARY_DIR}/matter.timestamp
   )

   list(APPEND executable_references ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

   add_dependencies(_${PROJECT_NAME} ${PROJECT_NAME}_matter)

endif()



list(APPEND executable_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
   core
   app_core_build)


if (MSVC)

   target_compile_options(_${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_${PROJECT_NAME} PRIVATE ${executable_references})

elseif(LINUX OR FREEBSD)

   target_compile_options(_${PROJECT_NAME} PRIVATE -fpermissive)
   #target_link_options(_${PROJECT_NAME} PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(_${PROJECT_NAME} PRIVATE ${executable_references})
   target_link_options(_${PROJECT_NAME} PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_${PROJECT_NAME} ${app_common_dependencies})
add_dependencies(_${PROJECT_NAME} experience_core)
add_dependencies(_${PROJECT_NAME} ${default_draw2d})
add_dependencies(_${PROJECT_NAME} ${default_imaging})
add_dependencies(_${PROJECT_NAME} ${default_write_text})
add_dependencies(_${PROJECT_NAME} database_sqlite3)
add_dependencies(_${PROJECT_NAME} regular_expression_pcre2)
add_dependencies(_${PROJECT_NAME} crypto_openssl)


target_include_directories(_${PROJECT_NAME} PRIVATE ${library_include_directories})

target_link_directories(_${PROJECT_NAME} PRIVATE ${library_link_directories})

set_target_properties(_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)





