cmake_minimum_required(VERSION 3.16)
project(app_integration CXX)


list(APPEND library_source
        _.cpp
        _.h
        ##_library.h
        #_factory.cpp
        application.cpp
        application.h
        document.cpp
        document.h
        framework.cpp
        framework.h
        frame.cpp
        frame.h
        impact.cpp
        impact.h
        main_frame.cpp
        main_frame.h
        render.cpp
        render.h
        render_1through3.cpp
        render_arcs.cpp
        render_box.cpp
        render_circle_path.cpp
        tab_impact.cpp
        tab_impact.h
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

set_target_properties(app_integration PROPERTIES LINKER_LANGUAGE CXX)


list(APPEND library_references
        acme
        apex
        aqua
        aura
        axis
        base
        )


if (MSVC)

    target_compile_options(app_integration PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(app_integration PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(app_integration PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(app_integration PRIVATE ${library_references} ${global_library_references})

elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)




    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_link_libraries(app_integration PRIVATE ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


target_link_directories(app_integration PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)


add_subdirectory(__implement)

