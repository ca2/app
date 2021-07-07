cmake_minimum_required(VERSION 3.17)
project(experience_tranquillum CXX)


list(APPEND library_source
        #_.cpp
        _.h
        #aaa_want_to_erase_experience_tranquillum_style.cpp
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
        style.cpp
        style.h)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   base)


add_library(experience_tranquillum SHARED ${library_source})


target_precompile_headers(experience_tranquillum PRIVATE framework.h)


set_target_properties(experience_tranquillum PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

    target_compile_options(experience_tranquillum PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(experience_tranquillum PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(experience_tranquillum PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/experience_tranquillum.lib")
    target_link_options(experience_tranquillum PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/experience_tranquillum.def")
    target_link_libraries(experience_tranquillum PRIVATE ${library_references})

elseif(LINUX)

    target_compile_options(experience_tranquillum PRIVATE -fpermissive)
    #target_link_options(experience_tranquillum PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(experience_tranquillum PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(experience_tranquillum PRIVATE -Wl,-z,defs)

endif()


target_include_directories(experience_tranquillum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(experience_tranquillum PRIVATE _APP_EXPERIENCE_TRANQUILLUM_LIBRARY)



