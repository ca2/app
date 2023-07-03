cmake_minimum_required(VERSION 3.16)
project(scripting CXX)


list(APPEND library_source
    _.cpp
    _.h
   #_library.h
   javascript/_.cpp
   javascript/_.h
   javascript/functions.cpp
   javascript/functions.h
   javascript/tinyjs_functions.cpp
   javascript/tinyjs_functions.h
    framework.cpp
    framework.h)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
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


set_target_properties(scripting PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(scripting PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(scripting PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(scripting PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/scripting.lib")
    target_link_options(scripting PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/scripting.def")
    target_link_libraries(scripting PRIVATE ${library_references})


elseif(${LINUX})


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    #target_link_options(scripting PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(scripting PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(scripting PRIVATE _SCRIPTING_LIBRARY)



