cmake_minimum_required(VERSION 3.16)
project(api_ca2 CXX)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   )


list(APPEND library_source
   _.cpp
   _.h
   api.cpp
   api.h
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

set_target_properties(api_ca2 PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)


    target_compile_options(api_ca2 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(api_ca2 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(api_ca2 PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(api_ca2 PRIVATE ${library_references})
    target_link_libraries(api_ca2 PRIVATE ws2_32 winmm shlwapi)


elseif(${LINUX} OR ${FREEBSD})


    target_compile_options(api_ca2 PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive>)
    target_link_libraries(api_ca2 PRIVATE ${library_references})
    target_link_options(api_ca2 PRIVATE -Wl,-z,defs)


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(api_ca2 PRIVATE _API_CA2_LIBRARY)



