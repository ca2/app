cmake_minimum_required(VERSION 3.16)
project(programming CXX)


list(APPEND library_source
    _.cpp
    _.h
   #_library.h
    framework.cpp
    framework.h
   dynamic_source/exit_exception.cpp
   dynamic_source/exit_exception.h
   dynamic_source/httpd_incoming_socket.cpp
   dynamic_source/httpd_incoming_socket.h
   dynamic_source/httpd_listen_socket.cpp
   dynamic_source/httpd_socket.h
   dynamic_source/script.cpp
   dynamic_source/script.h
   dynamic_source/script_cache.cpp
   dynamic_source/script_cache.h
   dynamic_source/script_compiler.cpp
   dynamic_source/script_compiler.cpp
   dynamic_source/script_composite.cpp
   dynamic_source/script_composite.h
   dynamic_source/script_instance.cpp
   dynamic_source/script_instance.h
   dynamic_source/script_interface.cpp
   dynamic_source/script_interface.h
   dynamic_source/script_main.cpp
   dynamic_source/script_main.h
   dynamic_source/script_manager.cpp
   dynamic_source/script_manager.h
   dynamic_source/session.cpp
   dynamic_source/session.h
   introjection/compiler.cpp
   introjection/compiler.h
   introjection/library.cpp
   introjection/library.h
   programming/_.h
   programming/_programming.h
   programming/compiler.cpp
   programming/compiler.h
   )



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


set_target_properties(programming PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(programming PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(programming PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(programming PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/programming.lib")
    target_link_options(programming PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/programming.def")
    target_link_libraries(programming PRIVATE ${library_references} ${global_library_references})


elseif(${LINUX})


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_link_libraries(programming PRIVATE dl ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



