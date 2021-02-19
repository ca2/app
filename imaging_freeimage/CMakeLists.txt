cmake_minimum_required(VERSION 3.17)
project(imaging_freeimage CXX)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if(LINUX)
elseif(WIN32)
elseif(UWP)
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND imaging_freeimage_source
        _.cpp
        _.h
        context_image.cpp
        context_image.h
        factory_exchange.cpp
        factory_exchange.h
        file_procedure.cpp
        file_procedure_ex1.cpp
        fimemory.h
        framework.cpp
        framework.h
        #imaging_freeimage.cpp
        loading.cpp
        loading_gif.cpp
        saving.cpp)


add_library(imaging_freeimage SHARED ${imaging_freeimage_source})


target_precompile_headers(imaging_freeimage PRIVATE framework.h)


set_target_properties(imaging_freeimage PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(imaging_freeimage PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_freeimage PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_freeimage PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/imaging_freeimage.lib")
    target_link_options(imaging_freeimage PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/imaging_freeimage.def")
    target_link_libraries(imaging_freeimage PRIVATE acme apex aqua aura freeimage)
elseif(LINUX)
    # pkg_check_modules(PKGCONFIG glib-2.0 gdk-3.0 gtk+-3.0 appindicator3-0.1)
    #pkg_check_modules(PKGCONFIG freetype2  )
    target_compile_options(imaging_freeimage PRIVATE -fpermissive)
    #target_compile_options(imaging_freeimage PRIVATE ${PKGCONFIG_CFLAGS})

    #target_compile_options(imaging_freeimage PRIVATE -std=c++14)
    #target_link_options(imaging_freeimage PRIVATE ${GTK_LDFLAGS})
    target_link_options(imaging_freeimage PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(imaging_freeimage PRIVATE z  dl  rt  bfd  X11  X11-xcb  xcb  xcb-util  Xinerama  Xmu  Xrandr  Xext  Xxf86vm  Xrender  Xi  ncurses  idn  pthread  sn)
    target_link_libraries(imaging_freeimage PRIVATE dl pthread X11 Xrandr Xrender Xinerama Xi ncurses sn freeimage)
    target_link_libraries(imaging_freeimage PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(imaging_freeimage PRIVATE acme apex aqua aura pcre2-8 sqlite3 bz2)
    target_link_options(imaging_freeimage PRIVATE -Wl,-z,defs)
    ##message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_link_directories(imaging_freeimage PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(imaging_freeimage PRIVATE .)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(imaging_freeimage PRIVATE $ENV{HOME}/__config)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)


target_compile_definitions(imaging_freeimage PRIVATE _imaging_freeimage_LIBRARY)
target_compile_definitions(imaging_freeimage PRIVATE UNICODE)
target_compile_definitions(imaging_freeimage PRIVATE _UNICODE)



