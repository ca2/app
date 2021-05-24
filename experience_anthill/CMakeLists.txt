cmake_minimum_required(VERSION 3.17)
project(experience_anthill CXX)


list(APPEND experience_anthill_source
        _.cpp
        _.h
        #aaa_want_to_erase_experience_anthill_style.cpp
        button.cpp
        button.h
        control_box.cpp
        control_box.h
        experience.cpp
        experience.h
        factory_exchange.cpp
        factory_exchange.h
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
        style.cpp
        style.h)


list(APPEND library_references
   acme apex aqua aura axis base)



add_library(experience_anthill SHARED ${experience_anthill_source})


target_precompile_headers(experience_anthill PRIVATE framework.h)


set_target_properties(experience_anthill PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

    target_compile_options(experience_anthill PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_anthill PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_anthill PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_anthill.lib")
    target_link_options(experience_anthill PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_anthill.def")
    target_link_libraries(experience_anthill PRIVATE ${library_references})

elseif(LINUX)

    target_compile_options(experience_anthill PRIVATE -fpermissive)
    target_link_options(experience_anthill PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(experience_anthill PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(experience_anthill PRIVATE -Wl,-z,defs)

endif()




target_include_directories(experience_anthill PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(experience_anthill PRIVATE _APP_EXPERIENCE_ANTHILL_LIBRARY)



