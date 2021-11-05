cmake_minimum_required(VERSION 3.17)
project(compress_bzip2 CXX)


list(APPEND library_source
        _.cpp
        _.h
        _compress_bzip2.h
        bz.cpp
        bz.h
        factory_exchange.cpp)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(compress_bzip2 SHARED ${library_source})

target_precompile_headers(compress_bzip2 PRIVATE framework.h)

set_target_properties(compress_bzip2 PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(compress_bzip2 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(compress_bzip2 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(compress_bzip2 PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/compress_bzip2.lib")
    target_link_options(compress_bzip2 PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/compress_bzip2.def")
    target_link_libraries(compress_bzip2 PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    target_compile_options(compress_bzip2 PRIVATE ${PKGCONFIG_CFLAGS})
    #target_link_options(compress_bzip2 PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(compress_bzip2 PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_options(compress_bzip2 PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(compress_bzip2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(compress_bzip2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(compress_bzip2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(compress_bzip2 PRIVATE _COMPRESS_BZIP2_LIBRARY)
