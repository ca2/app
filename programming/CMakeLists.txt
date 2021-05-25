cmake_minimum_required(VERSION 3.17)
project(programming CXX)


list(APPEND library_source
    _.cpp
    _.h
    framework.cpp
    framework.h)


add_library(programming SHARED ${library_source} _programming.h)


target_precompile_headers(programming PRIVATE framework.h)


set_target_properties(programming PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(programming PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(programming PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(programming PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/programming.lib")
    target_link_options(programming PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/programming.def")
    target_link_libraries(programming PRIVATE acme)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG freetype2 pango cairo pangocairo)
    target_compile_options(programming PRIVATE -fpermissive)
    target_compile_options(programming PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(programming PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(programming PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(programming PRIVATE acme apex aqua aura)
    target_link_options(programming PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(programming PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(programming PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(programming PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(programming PRIVATE _PROGRAMMING_LIBRARY)



