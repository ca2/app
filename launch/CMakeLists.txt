cmake_minimum_required(VERSION 3.16)
project(launch CXX)


list(APPEND executable_source
        #_curl.cpp
        #_wget.cpp
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

target_link_libraries(${PROJECT_NAME} PRIVATE ace)
add_dependencies(${PROJECT_NAME} ace)

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")

    set(LAUNCH_EXECUTABLE $ENV{HOME}/bin/launch)

else()

    set(LAUNCH_EXECUTABLE $ENV{HOME}/bin/launch)

endif()

message(STATUS "Output of LAUNCH_EXECUTABLE target custom_command dependency is \"${LAUNCH_EXECUTABLE}\"")

add_custom_command(
    OUTPUT ${LAUNCH_EXECUTABLE}
    COMMAND echo "Copying from \"$<TARGET_FILE:${PROJECT_NAME}>\" to \"${LAUNCH_EXECUTABLE}\""
    COMMAND cp $<TARGET_FILE:${PROJECT_NAME}> ${LAUNCH_EXECUTABLE}
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(deploy_${PROJECT_NAME} DEPENDS ${LAUNCH_EXECUTABLE})

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")

    set(STORE_EXECUTABLE $ENV{HOME}/store/linux/launch)

else()

    set(STORE_EXECUTABLE $ENV{HOME}/store/linux/launch)

endif()

message(STATUS "Output of STORE_EXECUTABLE target custom_command dependency is \"${STORE_EXECUTABLE}\"")

add_custom_command(
        OUTPUT ${STORE_EXECUTABLE}
        COMMAND echo "Copying from \"${LAUNCH_EXECUTABLE}\" to \"${STORE_EXECUTABLE}\""
        COMMAND cp ${LAUNCH_EXECUTABLE} ${STORE_EXECUTABLE}
        COMMAND chmod +x ${STORE_EXECUTABLE}
        DEPENDS ${LAUNCH_EXECUTABLE}
)

add_custom_target(store_${PROJECT_NAME} DEPENDS ${STORE_EXECUTABLE})


