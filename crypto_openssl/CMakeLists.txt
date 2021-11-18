cmake_minimum_required(VERSION 3.17)
project(crypto_openssl CXX)


list(APPEND library_source
   _.cpp
   _.h
   _crypto_openssl.h
   crypto.cpp
   crypto.h
   factory_exchange.cpp
   hasher.cpp
   hasher.h
   hasher_algorithm.cpp
   hasher_algorithm.h
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


add_library(crypto_openssl SHARED ${library_source})

target_precompile_headers(crypto_openssl PRIVATE framework.h)

set_target_properties(crypto_openssl PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(crypto_openssl PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(crypto_openssl PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(crypto_openssl PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/crypto_openssl.lib")
    target_link_options(crypto_openssl PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/crypto_openssl.def")
    target_link_libraries(crypto_openssl PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG libcrypto)
    target_compile_options(crypto_openssl PRIVATE ${PKGCONFIG_CFLAGS})
    #target_link_options(crypto_openssl PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(crypto_openssl PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(crypto_openssl PRIVATE ${library_references})
    target_link_options(crypto_openssl PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(crypto_openssl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(crypto_openssl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(crypto_openssl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(crypto_openssl PRIVATE _COMPRESS_BZIP2_LIBRARY)
