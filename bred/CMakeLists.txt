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
   user/user/user.cpp
   user/user/user.h
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
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(bred PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(bred PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(bred PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(bred PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/bred.lib")
    #target_link_options(bred PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/bred.def")
    target_link_libraries(bred PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_link_libraries(bred PRIVATE ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(bred PRIVATE UNICODE)
target_compile_definitions(bred PRIVATE _UNICODE)



