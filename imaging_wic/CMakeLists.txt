cmake_minimum_required(VERSION 3.17)
project(imaging_wic CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
    set(PLATFORM_NAME "linux")
    message("System is Linux")
    include(FindPkgConfig)
elseif(WIN32)
    set(PLATFORM_NAME "windows")
elseif(UWP)
    set(PLATFORM_NAME "uwp")
    set(WINDOWS_TSF TRUE)
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND imaging_wic_source
        _.cpp
        _.h
        context_image.cpp
        context_image.h
        factory_exchange.cpp
        factory_exchange.h
        framework.cpp
        framework.h
        loading.cpp
        loading_gif.cpp
        saving.cpp)


add_library(imaging_wic SHARED ${imaging_wic_source})


target_precompile_headers(imaging_wic PRIVATE framework.h)


set_target_properties(imaging_wic PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(imaging_wic PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_wic PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_wic PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/imaging_wic.lib")
    target_link_options(imaging_wic PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/imaging_wic.def")
    target_link_libraries(imaging_wic PRIVATE acme apex aqua aura windowscodecs)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG glib-2.0 gdk-3.0 gtk+-3.0 appindicator3-0.1)
    #pkg_check_modules(PKGCONFIG freetype2  )
    target_compile_options(imaging_wic PRIVATE -fpermissive)
    target_compile_options(imaging_wic PRIVATE ${PKGCONFIG_CFLAGS})

    #target_compile_options(imaging_wic PRIVATE -std=c++14)
    #target_link_options(imaging_wic PRIVATE ${GTK_LDFLAGS})
    target_link_options(imaging_wic PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(imaging_wic PRIVATE z  dl  rt  bfd  X11  X11-xcb  xcb  xcb-util  Xinerama  Xmu  Xrandr  Xext  Xxf86vm  Xrender  Xi  ncurses  idn  pthread  sn)
    target_link_libraries(imaging_wic PRIVATE dl pthread X11 Xrandr Xrender Xinerama Xi ncurses sn freeimage)
    target_link_libraries(imaging_wic PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(imaging_wic PRIVATE acme apex aqua aura pcre2-8 sqlite3 bz2)
    target_link_options(imaging_wic PRIVATE -Wl,-z,defs)
    ##message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_link_directories(imaging_wic PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(imaging_wic PRIVATE .)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(imaging_wic PRIVATE $ENV{HOME}/__config)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(imaging_wic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)


target_compile_definitions(imaging_wic PRIVATE _IMAGING_WIC_LIBRARY)
target_compile_definitions(imaging_wic PRIVATE UNICODE)
target_compile_definitions(imaging_wic PRIVATE _UNICODE)



