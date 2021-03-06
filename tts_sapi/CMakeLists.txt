cmake_minimum_required(VERSION 3.17)
project(draw2d_gdiplus CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
    set(PLATFORM_NAME "linux")
    include(FindPkgConfig)
elseif(WIN32)
    set(PLATFORM_NAME "windows")
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND draw2d_gdiplus_source
        _.cpp
        _.h
        bitmap.cpp
        bitmap.h
        brush.cpp
        brush.h
        factory_exchange.cpp
        font.cpp
        font.h
        framework.cpp
        framework.h
        graphics.cpp
        graphics.h
        image.cpp
        image.h
        object.cpp
        object.h
        path.cpp
        path.h
        pen.cpp
        pen.h
        preview_dc.cpp
        region.cpp
        region.h
        text.cpp)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(draw2d_gdiplus SHARED ${draw2d_gdiplus_source})

target_precompile_headers(draw2d_gdiplus PRIVATE framework.h)

set_target_properties(draw2d_gdiplus PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(draw2d_gdiplus PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_gdiplus PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_gdiplus PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/draw2d_gdiplus.lib")
    target_link_options(draw2d_gdiplus PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/draw2d_gdiplus.def")
    target_link_libraries(draw2d_gdiplus PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    target_compile_options(draw2d_gdiplus PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(draw2d_gdiplus PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(draw2d_gdiplus PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(draw2d_gdiplus PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(draw2d_gdiplus PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(draw2d_gdiplus PRIVATE $ENV{HOME}/__config)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(draw2d_gdiplus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(draw2d_gdiplus PRIVATE _DRAW2D_GDIPLUS_LIBRARY)
target_compile_definitions(draw2d_gdiplus PRIVATE UNICODE)
target_compile_definitions(draw2d_gdiplus PRIVATE _UNICODE)
