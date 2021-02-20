cmake_minimum_required(VERSION 3.17)
project(node_ansios CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
   set(LINUX TRUE)
   set(PLATFORM_NAME "linux")
   include(FindPkgConfig)
elseif (WIN32)
   set(PLATFORM_NAME "windows")
endif ()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND audio_alsa_source
   _.h
   _.cpp
   datetime.cpp
   factory_exchange.cpp
   factory_exchange.h
   framework.cpp
   framework.h
   #application.cpp
   #application.h
   node.cpp
   node.h
   )


list(APPEND library_references
   acme
   )


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


add_library(node_ansios SHARED ${audio_alsa_source} system_time.cpp system_color.cpp ../acme/node/posix/file_memory_map.cpp ../acme/node/posix/file_memory_map.h datetime.h)

target_precompile_headers(node_ansios PRIVATE framework.h)

set_target_properties(node_ansios PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(node_ansios PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(node_ansios PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(node_ansios PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(node_ansios PRIVATE ${library_references})
   add_dependencies(node_ansios draw2d_gdiplus)
elseif (LINUX)
   #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0)
   target_compile_options(node_ansios PRIVATE -fpermissive)
   target_compile_options(node_ansios PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(node_ansios PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(node_ansios PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_libraries(node_ansios PRIVATE asound)
   target_link_options(node_ansios PRIVATE -Wl,-z,defs)
   #add_dependencies(node_ansios acme)
endif ()


#add_dependencies(node_ansios experience_core)


target_link_directories(node_ansios PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(node_ansios PRIVATE .)
target_include_directories(node_ansios PRIVATE $ENV{HOME}/__config)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(node_ansios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_ansios PRIVATE _MUSIC_MIDI_ALSA_LIBRARY)
target_compile_definitions(node_ansios PRIVATE UNICODE)
target_compile_definitions(node_ansios PRIVATE _UNICODE)



