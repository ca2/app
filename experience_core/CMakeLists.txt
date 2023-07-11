cmake_minimum_required(VERSION 3.16)
project(experience_core CXX)


list(APPEND library_source
        #aaa_want_to_erase_experience_core_style.cpp
        experience/control_box_button.cpp
        experience/control_box_button.h
        experience/control_box.cpp
        experience/control_box.h
        experience/experience.cpp
        experience/experience.h
        experience/frame.cpp
        experience/frame.h
        experience/frame_001.cpp
        experience/frame_001.h
        experience/frame_002.cpp
        experience/frame_002.h
        experience/frame_005.cpp
        experience/frame_005.h
        experience/frame_008.cpp
        experience/frame_008.h
        experience/frame_011.cpp
        experience/frame_011.h
        experience/frame_013.cpp
        experience/frame_013.h
        experience/frame_Minimal001.cpp
        experience/frame_Minimal001.h
        user/style.cpp
        user/style.h
        user/_user.h
        _.cpp
        _.h
        _factory.cpp
        framework.cpp
        framework.h

        )

add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(experience_core PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(experience_core PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_core PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_core PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_core.lib")
    target_link_options(experience_core PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_core.def")
    target_link_libraries(experience_core PRIVATE acme apex aqua aura axis base)
elseif (${LINUX})


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    #target_link_options(experience_core PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(experience_core PRIVATE acme apex aqua aura axis base)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(experience_core PRIVATE _APP_EXPERIENCE_CORE_LIBRARY)



