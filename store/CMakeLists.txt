cmake_minimum_required(VERSION 3.16)
project(store CXX)


list(APPEND executable_source
        application.cpp
        application.h
)

add_executable(${PROJECT_NAME} ${executable_source})


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:CONSOLE")
endif ()

target_compile_definitions(${PROJECT_NAME} PRIVATE CUBE)

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

endif ()

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)

target_link_libraries(${PROJECT_NAME} PRIVATE static_launch_library)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(${FREEBSD})

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")

    set(LAUNCH_EXECUTABLE $ENV{HOME}/store/freebsd/store)

else()

    set(LAUNCH_EXECUTABLE $ENV{HOME}/store/freebsd/store)

endif()

endif()

message(STATUS "Output of LAUNCH_EXECUTABLE target custom_command dependency is \"${LAUNCH_EXECUTABLE}\"")

add_custom_command(
    OUTPUT ${LAUNCH_EXECUTABLE}
    COMMAND echo "Copying from \"$<TARGET_FILE:${PROJECT_NAME}>\" to \"${LAUNCH_EXECUTABLE}\""
    COMMAND cp $<TARGET_FILE:${PROJECT_NAME}> ${LAUNCH_EXECUTABLE}
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(deploy_${PROJECT_NAME} DEPENDS ${LAUNCH_EXECUTABLE})



