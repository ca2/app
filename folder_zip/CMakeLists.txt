cmake_minimum_required(VERSION 3.16)
project(folder_zip CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   _factory.cpp
   file.cpp
   file.h
   file_function_definitions.cpp
   file_function_definitions.h
   folder.cpp
   folder.h
   ioapi.cpp
   ioapi.h
   unzip.cpp
   unzip.h
   zip.cpp
   zip.h
   )



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(folder_zip PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(folder_zip PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(folder_zip PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(folder_zip PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/folder_zip.lib")
    target_link_options(folder_zip PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/folder_zip.def")
    target_link_libraries(folder_zip PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)

    if(NOT DONT_USE_PKG_CONFIG)
        pkg_check_modules(PKGCONFIG zlib)
    endif()
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(folder_zip PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(folder_zip PRIVATE ${PKGCONFIG_LIBRARIES} acme)
    target_link_options(folder_zip PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(folder_zip PRIVATE _FOLDER_ZIP_LIBRARY)
