cmake_minimum_required(VERSION 3.17)
project(experience_anthill CXX)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if(LINUX)
elseif(WIN32)
elseif(UWP)
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND experience_anthill_source
        _.cpp
        _.h
        #aaa_want_to_remove_experience_anthill_style.cpp
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


add_library(experience_anthill SHARED ${experience_anthill_source})


target_precompile_headers(experience_anthill PRIVATE framework.h)


set_target_properties(experience_anthill PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(experience_anthill PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_anthill PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_anthill PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_anthill.lib")
    target_link_options(experience_anthill PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_anthill.def")
    target_link_libraries(experience_anthill PRIVATE acme apex aqua aura axis base)
elseif(LINUX)
    target_compile_options(experience_anthill PRIVATE -fpermissive)
    target_link_options(experience_anthill PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(experience_anthill PRIVATE dl pthread X11 Xrandr Xrender Xinerama Xi ncurses)
    target_link_libraries(experience_anthill PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(experience_anthill PRIVATE acme apex aqua aura axis base)
    target_link_options(experience_anthill PRIVATE -Wl,-z,defs)
endif()


target_link_directories(experience_anthill PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(experience_anthill PRIVATE .)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(experience_anthill PRIVATE $ENV{HOME}/__config)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)


target_compile_definitions(experience_anthill PRIVATE _APP_EXPERIENCE_CORE_LIBRARY)
target_compile_definitions(experience_anthill PRIVATE UNICODE)
target_compile_definitions(experience_anthill PRIVATE _UNICODE)



