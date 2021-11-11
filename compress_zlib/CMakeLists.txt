cmake_minimum_required(VERSION 3.17)
project(compress_zlib CXX)


list(APPEND library_source
   _.cpp
   _.h
   _compress_zlib.h
   compress.cpp
   compress.h
   uncompress.cpp
   uncompress.h
   factory_exchange.cpp)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(compress_zlib SHARED ${library_source})

target_precompile_headers(compress_zlib PRIVATE framework.h)

set_target_properties(compress_zlib PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(compress_zlib PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(compress_zlib PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(compress_zlib PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/compress_zlib.lib")
    target_link_options(compress_zlib PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/compress_zlib.def")
    target_link_libraries(compress_zlib PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    target_compile_options(compress_zlib PRIVATE ${PKGCONFIG_CFLAGS})
    #target_link_options(compress_zlib PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(compress_zlib PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_options(compress_zlib PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(compress_zlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(compress_zlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(compress_zlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(compress_zlib PRIVATE _COMPRESS_BZIP2_LIBRARY)
