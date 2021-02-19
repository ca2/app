cmake_minimum_required(VERSION 3.17)
project(draw2d_cairo CXX)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
    set(PLATFORM_NAME "linux")
    message("System is Linux")
    include(FindPkgConfig)
elseif(WIN32)
    set(PLATFORM_NAME "windows")
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND draw2d_cairo_source
        _.cpp
        _.h
        bitmap.cpp
        bitmap.h
        brush.cpp
        brush.h
        cairo.cpp
        draw2d.cpp
        draw2d.h
        factory_exchange.cpp
        factory_exchange.h
        font.cpp
        font.h
        framework.cpp
        framework.h
        graphics.cpp
        graphics.h
        image.cpp
        image.h
        keep.cpp
        keep.h
        object.cpp
        object.h
        palette.cpp
        palette.h
        path.cpp
        path.h
        pen.cpp
        pen.h
        preview_dc.cpp
        region.cpp
        region.h)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(draw2d_cairo SHARED ${draw2d_cairo_source})

target_precompile_headers(draw2d_cairo PRIVATE framework.h)

set_target_properties(draw2d_cairo PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(draw2d_cairo PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_cairo PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_cairo PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/draw2d_cairo.lib")
    target_link_options(draw2d_cairo PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/draw2d_cairo.def")
    target_link_libraries(draw2d_cairo PRIVATE acme)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG freetype2 pango cairo pangocairo)
    #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0)
    target_compile_options(draw2d_cairo PRIVATE -fpermissive)
    target_compile_options(draw2d_cairo PRIVATE ${PKGCONFIG_CFLAGS})

    #target_compile_options(draw2d_cairo PRIVATE -std=c++14)
    #target_link_options(draw2d_cairo PRIVATE ${GTK_LDFLAGS})
    target_link_options(draw2d_cairo PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(draw2d_cairo PRIVATE )
    target_link_libraries(draw2d_cairo PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(draw2d_cairo PRIVATE acme apex aqua aura)
    target_link_options(draw2d_cairo PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(draw2d_cairo PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(apex PRIVATE .)
target_include_directories(draw2d_cairo PRIVATE $ENV{HOME}/__config)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(draw2d_cairo PRIVATE _AURA_LIBRARY)
target_compile_definitions(draw2d_cairo PRIVATE UNICODE)
target_compile_definitions(draw2d_cairo PRIVATE _UNICODE)



