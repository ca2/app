cmake_minimum_required(VERSION 3.17)
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
   topic.cpp
   topic.h
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
elseif(LINUX)
    pkg_check_modules(PKGCONFIG libpcre2-8)
    target_compile_options(regular_expression_pcre2 PRIVATE -fpermissive)
       target_compile_options(regular_expression_pcre2 PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(regular_expression_pcre2 PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(regular_expression_pcre2 PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(regular_expression_pcre2 PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(regular_expression_pcre2 PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(regular_expression_pcre2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(regular_expression_pcre2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(regular_expression_pcre2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(regular_expression_pcre2 PRIVATE _REGULAR_EXPRESSION_PCRE2_LIBRARY)



