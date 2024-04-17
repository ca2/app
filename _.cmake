# Created by camilo on 2023-02 <3ThomasBorregaardSorensen!!


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(WORKSPACE_FOLDER ${ROOT_SOURCE_DIR})


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

   message(STATUS "GNU Compiler")

   string(APPEND CMAKE_CXX_FLAGS "-fPIC -fexceptions -fnon-call-exceptions -frtti")

   #set(EXTRA_CXX_TARGET_COMPILER_OPTIONS "-ansi")

else()

   #set(EXTRA_CXX_TARGET_COMPILER_OPTIONS "")

endif ()


# default configuration
set(HAS_SYSTEM_UNAC FALSE)
set(HAS_APP_VERIWELL FALSE)
set(HAS_AUDIO_SYSTEM FALSE)
set(CURL_NANO_HTTP FALSE)
set(FREEBSD FALSE)
set(OPENBSD FALSE)
set(NETBSD FALSE)
set(DARWIN FALSE)
set(BSD FALSE)
set(LINUX FALSE)
set(MACOS FALSE)
set(HAS_NO_APPINDICATOR FALSE)



# In include(source/_.cmake) set variables like below
#set(INCLUDE_DRAW2D_CAIRO TRUE)
#set(INCLUDE_IMAGING_FREEIMAGE TRUE)
#set(INCLUDE_AUDIO TRUE)
include(source/_.cmake)


include(operating_system/_.cmake)


#if(${PLATFORM_NAME} STREQUAL "freebsd")
#   set(FREEBSD TRUE)
#   set(OPENBSD FALSE)
#   set(DARWIN TRUE)
#   set(BSD TRUE)
#   add_compile_definitions(FREEBSD)
#   add_compile_definitions(BSD_UNIX)
#elseif(${PLATFORM_NAME} STREQUAL "openbsd")
#   set(FREEBSD FALSE)
#   set(OPENBSD TRUE)
#   set(NETBSD FALSE)
#   set(DARWIN TRUE)
#   set(BSD TRUE)
#   add_compile_definitions(OPENBSD)
#   add_compile_definitions(BSD_UNIX)
#elseif(${PLATFORM_NAME} STREQUAL "netbsd")
#   set(FREEBSD FALSE)
#   set(OPENBSD FALSE)
#   set(NETBSD TRUE)
#   set(DARWIN TRUE)
#   set(BSD TRUE)
#   add_compile_definitions(NETBSD)
#   add_compile_definitions(BSD_UNIX)
#else()
#   set(FREEBSD FALSE)
#   set(OPENBSD FALSE)
#   set(NETBSD FALSE)
#   set(DARWIN FALSE)
#   set(BSD FALSE)
#endif()


#if(${PLATFORM_NAME} STREQUAL "linux")
#   set(LINUX TRUE)
#   set(WAYLAND TRUE)
#   add_compile_definitions(LINUX)
#else()
#   set(LINUX FALSE)
#   set(WAYLAND FALSE)
#   set(DISTRO "(NotApplicable)")
#endif()


if(NOT ${HAS_SYSTEM_UNAC})

   set(INCLUDE_UNAC TRUE)

endif()


add_subdirectory(source/app)
add_subdirectory(operating_system)
add_subdirectory(port)
add_subdirectory(source)



