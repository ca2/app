cmake_minimum_required(VERSION 3.16)
project(crypto_openssl CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   crypto.cpp
   crypto.h
   _factory.cpp
   hasher.cpp
   hasher.h
   hasher_algorithm.cpp
   hasher_algorithm.h
   initializer.cpp
   initializer.h
   rsa.cpp
   rsa.h
   )

list(APPEND library_references
   acme apex)


if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(crypto_openssl PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(crypto_openssl PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(crypto_openssl PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(crypto_openssl PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/crypto_openssl.lib")
    target_link_options(crypto_openssl PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/crypto_openssl.def")
    target_link_libraries(crypto_openssl PRIVATE ${library_references})
elseif(${LINUX})

    if(USE_PKGCONFIG)
        pkg_check_modules(PKGCONFIG libcrypto)
    endif()


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(crypto_openssl PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(crypto_openssl PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message(STATUS "PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(crypto_openssl PRIVATE _COMPRESS_BZIP2_LIBRARY)
