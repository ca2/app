cmake_minimum_required(VERSION 3.16)
project(_console_hellosolarsystem CXX)


list(APPEND executable_source
        unit_test/item.cpp
        unit_test/set.cpp
        unit_test/unit_test.cpp
        hellosolarsystem.cpp
        #tutor.cpp
        )

add_executable(${PROJECT_NAME} ${executable_source} unit_test/_unit_test.h)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:CONSOLE")
endif()


if(${LINUX})
    add_dependencies(${PROJECT_NAME} acme_linux apex_linux)
elseif(${FREEBSD})
    add_dependencies(${PROJECT_NAME} acme_freebsd apex_freebsd)
endif()


add_dependencies(${PROJECT_NAME} crypto_openssl)
add_dependencies(${PROJECT_NAME} folder_zip)


target_link_libraries(${PROJECT_NAME} PRIVATE acme apex)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories folder_zip)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _CONSOLE_HELLOSOLARSYSTEM_LIBRARY)



