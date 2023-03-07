cmake_minimum_required(VERSION 3.16)
project(bred CXX)


set(LIBRARY_NAME bred)


list(APPEND library_source
        const/idpool.cpp
        const/idpool.h
        include/_.h
        inline/__debug_box_clear_impl.h
        inline/__debug_box_set_impl.h
        #inline/_acid${PROJECT_NAME}.h
        #inline/${PROJECT_NAME}.h
        inline/_application.h
        inline/_console_old.h
        inline/_draw2d_impl.h
        inline/_new_impl.h
        inline/application.h
        inline/application_common.h
        inline/console.h
        inline/console_common.h
        inline/library.h
        platform/_platform.h
        platform/application.cpp
        platform/application.h
        platform/session.cpp
        platform/session.h
        platform/system.cpp
        platform/system.h
        _.cpp
        _.h
        _defer.h
        console.h
        framework.cpp
        framework.h
        id.h
        library.h)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   base)


add_library(${PROJECT_NAME} SHARED ${library_source})


target_precompile_headers(bred PRIVATE framework.h)


set_target_properties(bred PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(bred PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(bred PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(bred PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/bred.lib")
    target_link_options(bred PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/bred.def")
    target_link_libraries(bred PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


    target_compile_options(bred PRIVATE -fpermissive)
    target_link_libraries(bred PRIVATE ${library_references})
    target_link_options(bred PRIVATE -Wl,-z,defs)


endif()


target_link_directories(bred PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(bred PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(bred PRIVATE _BRED_LIBRARY)
target_compile_definitions(bred PRIVATE UNICODE)
target_compile_definitions(bred PRIVATE _UNICODE)



