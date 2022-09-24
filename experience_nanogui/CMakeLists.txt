cmake_minimum_required(VERSION 3.16)
project(experience_nanogui CXX)


list(APPEND library_source
        _.cpp
        _.h
        #aaa_want_to_erase_experience_nanogui_style.cpp
        experience/control_box_button.cpp
        experience/control_box_button.h
        experience/control_box.cpp
        experience/control_box.h
        experience/experience.cpp
        experience/experience.h
        _factory.cpp
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
        framework.cpp
        framework.h
        user/style.cpp
        user/style.h)


add_library(${PROJECT_NAME} SHARED ${library_source})


target_precompile_headers(experience_nanogui PRIVATE framework.h)


set_target_properties(experience_nanogui PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(experience_nanogui PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_nanogui PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_nanogui PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_nanogui.lib")
    target_link_options(experience_nanogui PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_nanogui.def")
    target_link_libraries(experience_nanogui PRIVATE acme apex aqua aura axis base)
elseif(LINUX)
    target_compile_options(experience_nanogui PRIVATE -fpermissive)
    #target_link_options(experience_nanogui PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(experience_nanogui PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(experience_nanogui PRIVATE acme apex aqua aura axis base)
    target_link_options(experience_nanogui PRIVATE -Wl,-z,defs)
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(experience_nanogui PRIVATE _APP_EXPERIENCE_NANOGUI_LIBRARY)



