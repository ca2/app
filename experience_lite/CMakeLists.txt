cmake_minimum_required(VERSION 3.16)
project(experience_lite CXX)


list(APPEND library_source
        #_.cpp
        _.h
        #aaa_want_to_erase_experience_lite_style.cpp
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


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


target_precompile_headers(experience_lite PRIVATE framework.h)


set_target_properties(experience_lite PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(experience_lite PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_lite PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_lite PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_lite.lib")
    target_link_options(experience_lite PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_lite.def")
    target_link_libraries(experience_lite PRIVATE acme apex aqua aura axis base)
elseif(LINUX)
    target_compile_options(experience_lite PRIVATE -fpermissive)
       target_compile_options(experience_lite PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(experience_lite PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(experience_lite PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(experience_lite PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(experience_lite PRIVATE acme apex aqua aura axis base)
    target_link_options(experience_lite PRIVATE -Wl,-z,defs)
endif()



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(experience_lite PRIVATE _APP_EXPERIENCE_LITE_LIBRARY)
target_compile_definitions(experience_lite PRIVATE UNICODE)
target_compile_definitions(experience_lite PRIVATE _UNICODE)



