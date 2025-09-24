cmake_minimum_required(VERSION 3.16)
project(launch CXX)


list(APPEND library_source
        application.cpp
        application.h
)


list(APPEND executable_source
        main.cpp
)


add_executable(${PROJECT_NAME} ${executable_source})

add_library(static_${PROJECT_NAME}_library STATIC ${library_source})


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:CONSOLE")
endif ()

target_compile_definitions(${PROJECT_NAME} PRIVATE CUBE)
target_compile_definitions(static_${PROJECT_NAME}_library PRIVATE CUBE)

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME}_library PRIVATE framework.h)

endif ()

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME}_library PRIVATE ${library_include_directories})

#target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)

if(${LINUX})
   target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
elseif(${FREEBSD})
   target_link_options(${PROJECT_NAME} PRIVATE -static)

elseif(${OPENBSD})
   target_link_options(${PROJECT_NAME} PRIVATE -static)
elseif(${NETBSD})
   target_link_options(${PROJECT_NAME} PRIVATE -static)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE static_acme)

if(${LINUX})
   target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
elseif(${FREEBSD})
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_posix)
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_darwin)
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_freebsd)
elseif(${OPENBSD})
   target_link_options(${PROJECT_NAME} PRIVATE -static)
elseif(${WIN32})
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_windows_common)
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_windows)
endif()

add_dependencies(static_${PROJECT_NAME}_library static_acme)



if(${LINUX})

target_link_libraries(${PROJECT_NAME} PRIVATE
        static_acme_linux)
        
endif()

if(NOT ${WINDOWS})
add_dependencies(static_${PROJECT_NAME}_library static_nano_compress_command_line)
add_dependencies(static_${PROJECT_NAME}_library static_nano_http_command_line)
endif()

#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#set_target_properties(static_${PROJECT_NAME}_library PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(${PROJECT_NAME} PRIVATE CUBE)
target_compile_definitions(static_${PROJECT_NAME}_library PRIVATE CUBE)


if(${__CMAKE_BUILD_TYPE} STREQUAL "Release")

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



