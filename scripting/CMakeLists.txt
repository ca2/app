cmake_minimum_required(VERSION 3.17)
project(scripting CXX)


list(APPEND library_source
    _.cpp
    _.h
   javascript/_.cpp
   javascript/_.h
   javascript/functions.cpp
   javascript/functions.h
    framework.cpp
    framework.h)


add_library(scripting SHARED ${library_source} _scripting.h)


target_precompile_headers(scripting PRIVATE framework.h)


set_target_properties(scripting PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(scripting PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(scripting PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(scripting PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/scripting.lib")
    target_link_options(scripting PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/scripting.def")
    target_link_libraries(scripting PRIVATE acme)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG freetype2 pango cairo pangocairo)
    target_compile_options(scripting PRIVATE -fpermissive)
    target_compile_options(scripting PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(scripting PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(scripting PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(scripting PRIVATE acme apex aqua aura)
    target_link_options(scripting PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(scripting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(scripting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(scripting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(scripting PRIVATE _SCRIPTING_LIBRARY)



