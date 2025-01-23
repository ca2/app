cmake_minimum_required(VERSION 3.16)
project(build CXX)


list(APPEND library_source
   _.h
   ${PROJECT_NAME}.h
   _build.h
   build.cpp
   build.h

   )


if(${LINUX})

   list(APPEND library_source
      linux.cpp
      linux.h)

endif()


list(APPEND library_references
   acme
   apex
   )


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})



target_link_directories(build PRIVATE ${library_link_directories})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(build PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(build PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_compile_options(build PRIVATE "/bigobj")
   target_link_options(build PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(build PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(build PRIVATE ${library_references} ${global_library_references})
elseif(${LINUX} OR ${__BSD__})
   target_compile_options(build PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   
   target_link_libraries(build PRIVATE ${library_references} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)

