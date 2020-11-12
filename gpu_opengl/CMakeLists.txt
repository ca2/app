cmake_minimum_required(VERSION 3.17)
project(gpu_opengl CXX)


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


list(APPEND gpu_opengl_source
        _.cpp
        _.h
        buffer.cpp
        buffer.h
        context.cpp
        context.h
        factory_exchange.cpp
        factory_exchange.h
        framework.cpp
        framework.h
        image_opengl.cpp
        opengl.cpp
        opengl.h
        program.cpp
        program.h
        shader.cpp
        shader.h)

if(WIN32)
    list(APPEND gpu_opengl_source
            context_win32.cpp
            context_win32.h
            )

endif()


if(LINUX)
    list(APPEND gpu_opengl_source
            context_egl.cpp
            context_egl.h
            context_glx.cpp
            context_glx.h
            )

    endif()


if(APPLE)
    list(APPEND gpu_opengl_source
            context_cgl.cpp
            context_cgl.h
            context_fbo.cpp
            context_fbo.h
            )

endif()


if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(gpu_opengl SHARED ${gpu_opengl_source})

target_precompile_headers(gpu_opengl PRIVATE framework.h)

set_target_properties(gpu_opengl PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(gpu_opengl PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(gpu_opengl PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(gpu_opengl PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/gpu_opengl.lib")
    target_link_options(gpu_opengl PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/gpu_opengl.def")
    target_link_libraries(gpu_opengl PRIVATE acme apex aqua aura glu32 glew32 opengl32)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG glib-2.0)
    #pkg_check_modules(PKGCONFIG freetype2 gtk+-3.0 )
    target_compile_options(gpu_opengl PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(gpu_opengl PRIVATE -std=c++14)
    #target_link_options(gpu_opengl PRIVATE ${GTK_LDFLAGS})
    target_link_options(gpu_opengl PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(gpu_opengl PRIVATE z  dl  rt  bfd  X11  X11-xcb  xcb  xcb-util  Xinerama  Xmu  Xrandr  Xext  Xxf86vm  Xrender  Xi  ncurses  idn  pthread  sn)
    target_link_libraries(gpu_opengl PRIVATE GL GLEW EGL GLU)
    target_link_libraries(gpu_opengl PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(gpu_opengl PRIVATE acme apex aqua aura)
    target_link_options(gpu_opengl PRIVATE -Wl,-z,defs)
    ##message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(gpu_opengl PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(gpu_opengl PRIVATE $ENV{HOME}/__config)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(gpu_opengl PRIVATE _GPU_OPENGL_LIBRARY)
target_compile_definitions(gpu_opengl PRIVATE UNICODE)
target_compile_definitions(gpu_opengl PRIVATE _UNICODE)



