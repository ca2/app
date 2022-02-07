cmake_minimum_required(VERSION 3.16)
project(regular_expression_pcre2 CXX)


list(APPEND regular_expression_pcre2_source
   _.cpp
   _.h
   context.cpp
   context.h
   _factory.cpp
   framework.cpp
   framework.h
   regular_expression.cpp
   regular_expression.h
   result.cpp
   result.h
)


list(APPEND library_references
   acme)

add_library(regular_expression_pcre2 SHARED ${regular_expression_pcre2_source})

target_precompile_headers(regular_expression_pcre2 PRIVATE framework.h)

set_target_properties(regular_expression_pcre2 PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(regular_expression_pcre2 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(regular_expression_pcre2 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(regular_expression_pcre2 PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/regular_expression_pcre2.lib")
    target_link_options(regular_expression_pcre2 PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/regular_expression_pcre2.def")
    target_link_libraries(regular_expression_pcre2 PRIVATE ${library_references})

elseif(LINUX OR FREEBSD)


   pkg_check_modules(PKGCONFIG libpcre2-8)
    target_compile_options(regular_expression_pcre2 PRIVATE -fpermissive)
    target_compile_options(regular_expression_pcre2 PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(regular_expression_pcre2 PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(regular_expression_pcre2 PRIVATE ${library_references})
    target_link_libraries(regular_expression_pcre2 PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_options(regular_expression_pcre2 PRIVATE -Wl,-z,defs)


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(regular_expression_pcre2 PRIVATE _REGULAR_EXPRESSION_PCRE2_LIBRARY)



