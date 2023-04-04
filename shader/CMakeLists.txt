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
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

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


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _APP_SHADER_LIBRARY)


#add_subdirectory(__implement)


add_subdirectory(__implement)

