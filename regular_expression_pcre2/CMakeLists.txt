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


list(APPEND static_library_references ${library_references} ${global_library_references})
list(TRANSFORM static_library_references PREPEND static_)


add_library(${PROJECT_NAME} SHARED ${regular_expression_pcre2_source})
add_library(static_${PROJECT_NAME} STATIC ${regular_expression_pcre2_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(regular_expression_pcre2 PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/regular_expression_pcre2.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/regular_expression_pcre2.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} pcre)

elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


    if (${USE_PKGCONFIG})
        pkg_check_modules(PKGCONFIG libpcre2-8)
    endif ()

    message(STATUS "(H) regular_expression_pcre2")
    message(STATUS "(H) PKGCONFIG_CFLAGS is ${${PROJECT_NAME}_PKGCONFIG_CFLAGS}")
    message(STATUS "(H) PKGCONFIG_LDFLAGS is ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS}")
    message(STATUS "(H) PKGCONFIG_LIBRARIES is ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES}")

    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})

    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})

    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(regular_expression_pcre2 PRIVATE _regular_expression_pcre2_project)



