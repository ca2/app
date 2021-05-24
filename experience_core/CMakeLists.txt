cmake_minimum_required(VERSION 3.17)
project(experience_core CXX)


list(APPEND experience_core_source
        _.cpp
        _.h
        #aaa_want_to_erase_experience_core_style.cpp
        button.cpp
        button.h
        control_box.cpp
        control_box.h
        experience.cpp
        experience.h
        factory_exchange.cpp
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
        library.h
        style.cpp
        style.h)


add_library(experience_core SHARED ${experience_core_source})


target_precompile_headers(experience_core PRIVATE framework.h)


set_target_properties(experience_core PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(experience_core PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_core PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_core PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_core.lib")
    target_link_options(experience_core PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_core.def")
    target_link_libraries(experience_core PRIVATE acme apex aqua aura axis base)
elseif(LINUX)
    target_compile_options(experience_core PRIVATE -fpermissive)
    target_link_options(experience_core PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(experience_core PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(experience_core PRIVATE acme apex aqua aura axis base)
    target_link_options(experience_core PRIVATE -Wl,-z,defs)
endif()


target_include_directories(experience_core PRIVATE .)
target_include_directories(experience_core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(experience_core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(experience_core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(experience_core PRIVATE _APP_EXPERIENCE_CORE_LIBRARY)



