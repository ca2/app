cmake_minimum_required(VERSION 3.16)
project(compress_bzip2 CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_compress_bzip2.h
   compress.cpp
   compress.h
   uncompress.cpp
   uncompress.cpp
   _factory.cpp)


list(APPEND library_references
   acme
   )


if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(compress_bzip2 PRIVATE framework.h)

set_target_properties(compress_bzip2 PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(compress_bzip2 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(compress_bzip2 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(compress_bzip2 PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/compress_bzip2.lib")
   target_link_options(compress_bzip2 PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/compress_bzip2.def")
   target_link_libraries(compress_bzip2 PRIVATE acme apex aqua aura Gdiplus)


elseif(LINUX)


if(DEFINED UBUNTU OR DEFINED DEBIAN OR DEFINED RASPBIAN)


   list(APPEND library_references
      bz2)

   message("including bz2 \"manually\" at ubuntu/debian")


else()


   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG bzip2)
   endif()
   target_compile_options(compress_bzip2 PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(compress_bzip2 PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(compress_bzip2 PRIVATE ${PKGCONFIG_LIBRARIES})


endif()


   target_link_libraries(compress_bzip2 PRIVATE ${library_references})
   target_link_options(compress_bzip2 PRIVATE -Wl,-z,defs)
   #message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(compress_bzip2 PRIVATE _COMPRESS_BZIP2_LIBRARY)
