cmake_minimum_required(VERSION 3.17)
project(experience_tranquillum CXX)


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


list(APPEND experience_tranquillum_source
        _.cpp
        _.h
        #aaa_want_to_remove_experience_tranquillum_style.cpp
        button.cpp
        button.h
        control_box.cpp
        control_box.h
        experience.cpp
        experience.h
        frame.cpp
        frame.h
        frame_001.cpp
        frame_001.h
        frame_002.cpp
        frame_002.h
        frame_005.cpp
        frame_005.h
        frame_008.cpp
        frame_008.h
        frame_011.cpp
        frame_011.h
        frame_013.cpp
        frame_013.h
        frame_Minimal001.cpp
        frame_Minimal001.h
        framework.cpp
        framework.h
        library.cpp
        library.h
        style.cpp
        style.h)






if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(experience_tranquillum SHARED ${experience_tranquillum_source})


target_precompile_headers(experience_tranquillum PRIVATE framework.h)


set_target_properties(experience_tranquillum PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(experience_tranquillum PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_tranquillum PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_tranquillum PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_tranquillum.lib")
    target_link_options(experience_tranquillum PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_tranquillum.def")
    target_link_libraries(experience_tranquillum PRIVATE acme apex aqua aura axis base)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG glib-2.0 gdk-3.0 gtk+-3.0 appindicator3-0.1)
    #pkg_check_modules(PKGCONFIG freetype2  )
    target_compile_options(experience_tranquillum PRIVATE -fpermissive)
    target_compile_options(experience_tranquillum PRIVATE ${PKGCONFIG_CFLAGS})

    #target_compile_options(experience_tranquillum PRIVATE -std=c++14)
    #target_link_options(experience_tranquillum PRIVATE ${GTK_LDFLAGS})
    target_link_options(experience_tranquillum PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(experience_tranquillum PRIVATE z  dl  rt  bfd  X11  X11-xcb  xcb  xcb-util  Xinerama  Xmu  Xrandr  Xext  Xxf86vm  Xrender  Xi  ncurses  idn  pthread  sn)
    target_link_libraries(experience_tranquillum PRIVATE dl pthread X11 Xrandr Xrender Xinerama Xi ncurses sn)
    target_link_libraries(experience_tranquillum PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(experience_tranquillum PRIVATE acme apex aqua aura axis base)
    target_link_options(experience_tranquillum PRIVATE -Wl,-z,defs)
    ##message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_link_directories(experience_tranquillum PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(experience_tranquillum PRIVATE .)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(experience_tranquillum PRIVATE $ENV{HOME}/__config)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)


target_compile_definitions(experience_tranquillum PRIVATE _APP_EXPERIENCE_CORE_LIBRARY)
target_compile_definitions(experience_tranquillum PRIVATE UNICODE)
target_compile_definitions(experience_tranquillum PRIVATE _UNICODE)



