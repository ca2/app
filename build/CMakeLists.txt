cmake_minimum_required(VERSION 3.17)
project(build CXX)


list(APPEND library_source
   _.h
   _app_build.h
   _build.h
   build.cpp
   build.h

   )


if(LINUX)

   list(APPEND library_source
      linux.cpp
      linux.h)

endif()


list(APPEND library_references
   acme
   apex
   )


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


add_library(build SHARED ${library_source})


target_include_directories(build PRIVATE ${library_include_directories})


target_link_directories(build PRIVATE ${library_link_directories})


target_precompile_headers(build PRIVATE framework.h)


set_target_properties(build PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(build PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_compile_options(build PRIVATE "/bigobj")
   target_link_options(build PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(build PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(build PRIVATE ${library_references})
elseif(LINUX OR FREEBSD)
   target_compile_options(build PRIVATE -fpermissive)
   #target_link_options(build PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(build PRIVATE ${library_references})
   target_link_options(build PRIVATE -Wl,-z,defs)
endif ()


target_compile_definitions(build PRIVATE _build_LIBRARY)

