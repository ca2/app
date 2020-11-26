cmake_minimum_required(VERSION 3.17)
project(app_shader CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
    set(PLATFORM_NAME "linux")
    include(FindPkgConfig)
elseif(WIN32)
    set(PLATFORM_NAME "windows")
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND app_shader_source
    _.h
    _user.h
    application.cpp
    application.h
    framework.h
    render.cpp
    render.h
    window.cpp
    window.h)


if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_executable(app_shader ${app_shader_source})

target_precompile_headers(app_shader PRIVATE framework.h)

set_target_properties(app_shader PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(app_shader PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_shader PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_shader PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_shader PRIVATE acme apex aqua aura)
    add_dependencies(app_shader draw2d_gdiplus)
elseif(LINUX)
    target_link_options(app_shader PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(app_shader PRIVATE acme apex aqua aura)
    target_link_options(app_shader PRIVATE -Wl,-z,defs)
    add_dependencies(app_shader draw2d_cairo)
endif()


add_dependencies(app_shader gpu_opengl)


target_link_directories(app_shader PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(app_shader PRIVATE .)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive)
target_include_directories(app_shader PRIVATE $ENV{HOME}/__config)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/inc)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(app_shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(app_shader PRIVATE $ENV{HOME}/__sensitive)


target_compile_definitions(app_shader PRIVATE _APP_SHADER_LIBRARY)
target_compile_definitions(app_shader PRIVATE UNICODE)
target_compile_definitions(app_shader PRIVATE _UNICODE)



