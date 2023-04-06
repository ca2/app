cmake_minimum_required(VERSION 3.16)
project(compress_zlib CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   compress.cpp
   compress.h
   uncompress.cpp
   uncompress.h
   _factory.cpp)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(compress_zlib PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(compress_zlib PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(compress_zlib PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(compress_zlib PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/compress_zlib.lib")
    target_link_options(compress_zlib PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/compress_zlib.def")
    target_link_libraries(compress_zlib PRIVATE acme apex)
elseif(LINUX)

    if(NOT DONT_USE_PKG_CONFIG)
        pkg_check_modules(PKGCONFIG zlib)
    endif()


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(compress_zlib PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(compress_zlib PRIVATE ${PKGCONFIG_LIBRARIES} acme)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(compress_zlib PRIVATE _COMPRESS_ZLIB_LIBRARY)
