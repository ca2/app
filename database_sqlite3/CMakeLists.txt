cmake_minimum_required(VERSION 3.16)
project(database_sqlite3 CXX)


list(APPEND database_sqlite3_source
   _.cpp
   _.h
   ##_library.h
   _factory.cpp
   database.cpp
   database.h
   framework.cpp
   framework.h
)

list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis)


add_library(${PROJECT_NAME} SHARED ${database_sqlite3_source})
add_library(static_${PROJECT_NAME} STATIC ${database_sqlite3_source})


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(database_sqlite3 PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)


   target_compile_options(database_sqlite3 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(database_sqlite3 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(database_sqlite3 PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/database_sqlite3.lib")
   target_link_options(database_sqlite3 PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/database_sqlite3.def")
   target_link_libraries(database_sqlite3 PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG sqlite3)
   endif()


   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(database_sqlite3 PRIVATE -fpermissive)
   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(database_sqlite3 PRIVATE ${library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

   message(STATUS "PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(database_sqlite3 PRIVATE _DATABASE_SQLITE3_LIBRARY)



