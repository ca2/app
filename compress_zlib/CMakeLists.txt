cmake_minimum_required(VERSION 3.16)
project(compress_zlib CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   compress.cpp
   compress.h
   uncompress.cpp
   uncompress.h
   _factory.cpp)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
endif()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

list(APPEND library_references
   acme)

list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(static_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/compress_zlib.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/compress_zlib.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex)
elseif (${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})


    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    target_compile_features(static_${PROJECT_NAME} PRIVATE cxx_std_20)


    if(USE_PKGCONFIG)
        pkg_check_modules(PKGCONFIG zlib)
    endif()


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(compress_zlib PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES} ${static_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message(STATUS "(9) PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



