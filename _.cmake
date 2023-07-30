# Created by camilo on 2023-02 <3ThomasBorregaardSorensen!!


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
set(ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(WORKSPACE_FOLDER ${ROOT_SOURCE_DIR})


# default configuration
set(HAS_SYSTEM_UNAC FALSE)
set(HAS_APP_VERIWELL FALSE)
set(HAS_AUDIO_SYSTEM FALSE)
set(CURL_NANO_HTTP FALSE)


# In include(source/_.cmake) set variables like below
#set(INCLUDE_DRAW2D_CAIRO TRUE)
#set(INCLUDE_IMAGING_FREEIMAGE TRUE)
#set(INCLUDE_AUDIO TRUE)
include(source/_.cmake)



include(operating_system/_.cmake)


if(${PLATFORM_NAME} STREQUAL "freebsd")
   set(FREEBSD TRUE)
   set(OPENBSD FALSE)
   set(DARWIN TRUE)
   set(BSD TRUE)
   add_compile_definitions(FREEBSD)
elseif(${PLATFORM_NAME} STREQUAL "openbsd")
   set(FREEBSD FALSE)
   set(OPENBSD TRUE)
   set(DARWIN TRUE)
   set(BSD TRUE)
   add_compile_definitions(FREEBSD)
else()
   set(FREEBSD FALSE)
   set(OPENBSD FALSE)
   set(DARWIN FALSE)
   set(BSD FALSE)
endif()


if(${PLATFORM_NAME} STREQUAL "linux")
   set(LINUX TRUE)
   add_compile_definitions(LINUX)
else()
   set(LINUX FALSE)
   set(DISTRO "(NotApplicable)")
endif()


add_subdirectory(source/app)
add_subdirectory(operating_system)
add_subdirectory(port)
add_subdirectory(source)



