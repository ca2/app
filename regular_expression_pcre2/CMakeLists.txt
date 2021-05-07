cmake_minimum_required(VERSION 3.17)
project(database_sqlite3 CXX)


list(APPEND database_sqlite3_source
        _.cpp
        _.h
        database.cpp
        database.h
        factory_exchange.cpp
        factory_exchange.h
        framework.cpp
        framework.h
)


add_library(database_sqlite3 SHARED ${database_sqlite3_source} _impl.h)

target_precompile_headers(database_sqlite3 PRIVATE framework.h)

set_target_properties(database_sqlite3 PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(database_sqlite3 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(database_sqlite3 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(database_sqlite3 PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/database_sqlite3.lib")
    target_link_options(database_sqlite3 PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/database_sqlite3.def")
    target_link_libraries(database_sqlite3 PRIVATE acme)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(database_sqlite3 PRIVATE -fpermissive)
    target_compile_options(database_sqlite3 PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(database_sqlite3 PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(database_sqlite3 PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(database_sqlite3 PRIVATE acme apex aqua aura)
    target_link_options(database_sqlite3 PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(database_sqlite3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(database_sqlite3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(database_sqlite3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(database_sqlite3 PRIVATE _DATABASE_SQLITE3_LIBRARY)



