cmake_minimum_required(VERSION 3.16)
project(launch CXX)


list(APPEND library_source
   application.cpp
   application.h
   launch.cpp
   launch.h
)


list(APPEND executable_source
   main.cpp
)


add_executable(${PROJECT_NAME} ${executable_source})

add_library(static_${PROJECT_NAME}_library STATIC ${library_source})


if(${WIN32})






   if(MSVC)


      target_compile_options(${PROJECT_NAME} PRIVATE    "/MD$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE    "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE    "/SUBSYSTEM:WINDOWS")
      target_link_options(${PROJECT_NAME} PRIVATE    "/bigobj")
      target_link_options(${PROJECT_NAME} PRIVATE    "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
      target_link_options(${PROJECT_NAME} PRIVATE    "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")


   else()


      target_link_options(${PROJECT_NAME} PRIVATE "-mwindows")
      target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")


   endif()



endif ()

target_compile_definitions(${PROJECT_NAME} PRIVATE CUBE)
target_compile_definitions(static_${PROJECT_NAME}_library PRIVATE CUBE)

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)
    target_precompile_headers(static_${PROJECT_NAME}_library PRIVATE platform.h)

endif ()

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME}_library PRIVATE ${library_include_directories})

#target_link_options(${PROJECT_NAME} PRIVATE ${LINK_STATIC_OPTION} -static-libgcc -static-libstdc++)

if(${LINUX})
   target_link_options(${PROJECT_NAME} PRIVATE ${LINK_STATIC_OPTION} -static-libgcc -static-libstdc++)
elseif(${FREEBSD})
	target_link_options(${PROJECT_NAME} PRIVATE ${LINK_STATIC_OPTION})
	target_link_libraries(${PROJECT_NAME} PRIVATE procstat kvm util)
elseif(${OPENBSD})
   target_link_options(${PROJECT_NAME} PRIVATE ${LINK_STATIC_OPTION})
elseif(${NETBSD})
   target_link_options(${PROJECT_NAME} PRIVATE ${LINK_STATIC_OPTION})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE static_acme)

if(${LINUX})
   target_link_options(${PROJECT_NAME} PRIVATE ${LINK_STATIC_OPTION} -static-libgcc -static-libstdc++)
elseif(${FREEBSD})
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_posix)
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_darwin)
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_freebsd)
elseif(${OPENBSD})
   target_link_options(${PROJECT_NAME} PRIVATE ${LINK_STATIC_OPTION})
elseif(${WIN32})
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_windows_common)
   target_link_libraries(${PROJECT_NAME} PRIVATE static_acme_windows)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE static_acme)
target_link_libraries(${PROJECT_NAME} PRIVATE static_${PROJECT_NAME}_library)



if(${LINUX})

target_link_libraries(${PROJECT_NAME} PRIVATE
        static_acme_linux)
        
endif()

if(${LINUX} OR ${__BSD__} OR ${__APPLE__})
target_link_libraries(${PROJECT_NAME} PRIVATE static_nano_compress_command_line)
target_link_libraries(${PROJECT_NAME} PRIVATE static_nano_http_command_line)
endif()


if(${__CMAKE_BUILD_TYPE} STREQUAL "Release")

    set(LAUNCH_EXECUTABLE ${HOME_DIR}/bin/launch)

else()

    set(LAUNCH_EXECUTABLE ${HOME_DIR}/bin/launch)

endif()

message(STATUS "Output of LAUNCH_EXECUTABLE target custom_command dependency is \"${LAUNCH_EXECUTABLE}\"")

ca2_add_up_to_date_copy(deploy_${PROJECT_NAME} ${PROJECT_NAME} "${LAUNCH_EXECUTABLE}")



