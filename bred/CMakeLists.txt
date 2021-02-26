cmake_minimum_required(VERSION 3.17)
project(bred CXX)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if(LINUX)
elseif(WIN32)
elseif(UWP)
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND bred_source
        const/idpool.cpp
        const/idpool.h
        include/_.h
        inline/__debug_box_clear_impl.h
        inline/__debug_box_set_impl.h
        inline/_acid_app_impl.h
        inline/_app_impl1.h
        inline/_application.h
        inline/_console_old.h
        inline/_draw2d_impl.h
        inline/_new_impl.h
        inline/application.h
        inline/application_common.h
        inline/console.h
        inline/console_common.h
        inline/library.h
        platform/_platform.h
        platform/application.cpp
        platform/application.h
        platform/session.cpp
        platform/session.h
        platform/system.cpp
        platform/system.h
        _.cpp
        _.h
        _defer.h
        console.h
        framework.cpp
        framework.h
        id.h
        library.h)




if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(bred SHARED ${bred_source})


target_precompile_headers(bred PRIVATE framework.h)


set_target_properties(bred PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(bred PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(bred PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(bred PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/bred.lib")
    target_link_options(bred PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/bred.def")
    target_link_libraries(bred PRIVATE acme apex aqua aura axis base)
elseif(LINUX)
    #pkg_check_modules(PKGCONFIG glib-2.0 gdk-3.0 gtk+-3.0 appindicator3-0.1)
    #pkg_check_modules(PKGCONFIG freetype2  )
    target_compile_options(bred PRIVATE -fpermissive)
    #target_compile_options(bred PRIVATE ${PKGCONFIG_CFLAGS})

    #target_compile_options(bred PRIVATE -std=c++14)
    #target_link_options(bred PRIVATE ${GTK_LDFLAGS})
    target_link_options(bred PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(bred PRIVATE z  dl  rt  bfd  X11  X11-xcb  xcb  xcb-util  Xinerama  Xmu  Xrandr  Xext  Xxf86vm  Xrender  Xi  ncurses  idn  pthread  sn)
    target_link_libraries(bred PRIVATE dl pthread X11 Xrandr Xrender Xinerama Xi ncurses)
    target_link_libraries(bred PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(bred PRIVATE acme apex aqua aura axis base)
    target_link_options(bred PRIVATE -Wl,-z,defs)
    ##message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_link_directories(bred PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(bred PRIVATE .)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(bred PRIVATE $ENV{HOME}/__config)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)


target_compile_definitions(bred PRIVATE _BRED_LIBRARY)
target_compile_definitions(bred PRIVATE UNICODE)
target_compile_definitions(bred PRIVATE _UNICODE)



