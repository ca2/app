cmake_minimum_required(VERSION 3.16)
project(experience_tranquillum CXX)


list(APPEND library_source
        #_.cpp
        _.h
        #aaa_want_to_erase_experience_tranquillum_style.cpp
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
        experience/frame_022.cpp
        experience/frame_022.h
        experience/frame_Minimal001.cpp
        experience/frame_Minimal001.h
        framework.cpp
        framework.h
        user/style.cpp
        user/style.h)


list(APPEND library_references
    acme
    apex
    aqua
    aura
    axis
    base)


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


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

if (MSVC)

    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_tranquillum.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_tranquillum.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})

elseif(${LINUX} OR ${ANDROID})


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_link_libraries(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



