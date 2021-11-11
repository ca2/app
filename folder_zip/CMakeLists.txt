cmake_minimum_required(VERSION 3.17)
project(folder_zip CXX)


list(APPEND library_source
   _.cpp
   _.h
   _folder_zip.h
   factory_exchange.cpp
   file.cpp
   file.h
   file_function_definitions.cpp
   file_function_definitions.h
   folder.cpp
   folder.h
   ioapi.cpp
   ioapi.h
   unzip.cpp
   unzip.h
   zip.cpp
   zip.h
   )



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(folder_zip SHARED ${library_source})

target_precompile_headers(folder_zip PRIVATE framework.h)

set_target_properties(folder_zip PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(folder_zip PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(folder_zip PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(folder_zip PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/folder_zip.lib")
    target_link_options(folder_zip PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/folder_zip.def")
    target_link_libraries(folder_zip PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    target_compile_options(folder_zip PRIVATE ${PKGCONFIG_CFLAGS})
    #target_link_options(folder_zip PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(folder_zip PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_options(folder_zip PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(folder_zip PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(folder_zip PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(folder_zip PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(folder_zip PRIVATE _COMPRESS_BZIP2_LIBRARY)
