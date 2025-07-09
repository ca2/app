# Created by camilo on 2023-02 <3ThomasBorregaardSorensen!!
set(INCLUDE_IMAGING_FREEIMAGE FALSE)
set(INCLUDE_FREEIMAGE FALSE)
set(WIN32 FALSE)
set(__APPLE__ FALSE)

set(CMAKE_CXX_STANDARD 20)


if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
   message(STATUS "Target system is x86 or x86_64 architecture.")
   # You can set a variable or perform specific actions here
   set(IS_X86_ARCH TRUE)
else()
   message(STATUS "Target system is not x86 or x86_64 architecture.")
   set(IS_X86_ARCH FALSE)
endif()


if("${CMAKE_BUILD_TYPE}" STREQUAL "")

   set(__CMAKE_BUILD_TYPE "Debug")

else()

   set(__CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}")

endif()



message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
message(STATUS "PATH is $ENV{PATH}")




set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(WORKSPACE_FOLDER ${ROOT_SOURCE_DIR})
set(APPLICATION_BUILD_HELPER_BINARY "$ENV{HOME}/bin/application_build_helper")


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
set(APPLE FALSE)
set(SOLARIS FALSE)
set(MACOS FALSE)
set(SUSE FALSE)
set(FREEBSD FALSE)
set(NETBSD FALSE)
set(OPENBSD FALSE)
set(UBUNTU FALSE)
set(DEBIAN FALSE)
set(ANDROID FALSE)
set(HAS_NO_APPINDICATOR FALSE)



message(STATUS "going to include \"source/_.cmake\"")
include(source/_.cmake)


if(NOT DEFINED DESKTOP_AMBIENT)

   set(DESKTOP_AMBIENT TRUE)

endif()


message(STATUS "going to include \"operating_system/_.cmake\"")
include(operating_system/_.cmake)




if(NOT ${HAS_SYSTEM_UNAC})

   set(INCLUDE_UNAC TRUE)

endif()


add_subdirectory(operating_system)
add_subdirectory(port)
add_subdirectory(source/app)
add_subdirectory(source)


add_subdirectory(source/app/launch)



