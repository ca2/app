cmake_minimum_required(VERSION 3.17)
project(app_app CXX)

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


list(APPEND app_app_source
        _.h
        _user.h
        application.cpp
        application.h
        framework.cpp
        framework.h
        window.cpp
        window.h)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_executable(app_app ${app_app_source})

target_precompile_headers(app_app PRIVATE framework.h)

set_target_properties(app_app PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_app PRIVATE acme apex aqua aura)
elseif(LINUX)
    #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
    #pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    #target_compile_options(app_app PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(app_app PRIVATE -std=c++14)
    #target_link_options(app_app PRIVATE ${GTK_LDFLAGS})
    target_link_options(app_app PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(app_app PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_libraries(app_app PRIVATE acme apex aqua aura)
    target_link_options(app_app PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(app_app PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(app_app PRIVATE .)
target_include_directories(app_app PRIVATE $ENV{HOME}/__config)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_app PRIVATE _APP_APP_LIBRARY)
target_compile_definitions(app_app PRIVATE UNICODE)
target_compile_definitions(app_app PRIVATE _UNICODE)
