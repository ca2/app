cmake_minimum_required(VERSION 3.17)
project(app_app CXX)


list(APPEND app_app_source
        _.cpp
        _.h
        _user.h
        application.cpp
        application.h
        framework.cpp
        framework.h
        main_window.cpp
        main_window.h)


add_executable(app_app ${app_app_source})

target_precompile_headers(app_app PRIVATE framework.h)

set_target_properties(app_app PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(app_app PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_app PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_app PRIVATE acme apex aqua aura)
    add_dependencies(app_app draw2d_gdiplus)
elseif(LINUX)

    target_link_options(app_app PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(app_app PRIVATE acme apex aqua aura)
    target_link_options(app_app PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
    add_dependencies(app_app draw2d_cairo)
endif()

add_dependencies(app_app ${app_common_dependencies})
add_dependencies(app_app apex_linux)

target_link_directories(app_app PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(app_app PRIVATE .)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(app_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_app PRIVATE _APP_APP_LIBRARY)
