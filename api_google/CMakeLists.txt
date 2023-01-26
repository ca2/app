cmake_minimum_required(VERSION 3.16)
project(api_google CXX)


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

target_precompile_headers(api_google PRIVATE framework.h)

set_target_properties(api_google PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)


   target_compile_options(api_google PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(api_google PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(api_google PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(api_google PRIVATE ${library_references})
   target_link_libraries(api_google PRIVATE ws2_32 winmm shlwapi)


elseif(LINUX OR FREEBSD)


   target_compile_options(api_google PRIVATE -fpermissive)
   target_link_libraries(api_google PRIVATE ${library_references})
   target_link_options(api_google PRIVATE -Wl,-z,defs)


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(api_google PRIVATE _API_AZURE_LIBRARY)



