# Created by camilo on 2023-02 <3ThomasBorregaardSorensen!!


if("${CMAKE_BUILD_TYPE}" STREQUAL "")

   set(__CMAKE_BUILD_TYPE "Debug")

else()

   set(__CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}")

endif()




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
set(__BSD__ FALSE)
set(LINUX FALSE)
set(MACOS FALSE)
set(SUSE FALSE)
set(HAS_NO_APPINDICATOR FALSE)




include(source/_.cmake)




include(operating_system/_.cmake)




if(NOT ${HAS_SYSTEM_UNAC})

   set(INCLUDE_UNAC TRUE)

endif()





add_subdirectory(source/app)
add_subdirectory(operating_system)
add_subdirectory(port)
add_subdirectory(source)


add_subdirectory(source/app/launch)



