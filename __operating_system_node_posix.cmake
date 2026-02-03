# Created by camilo on 2026-01-04 14:54 ThomasBorregaardSørensen!!



execute_process(COMMAND uname -m OUTPUT_VARIABLE __SYSTEM_ARCHITECTURE)
string(STRIP ${__SYSTEM_ARCHITECTURE} __SYSTEM_ARCHITECTURE)
message(STATUS "__SYSTEM_ARCHITECTURE is ${__SYSTEM_ARCHITECTURE}")


if(EXISTS "${CMAKE_SOURCE_DIR}/raspberrypios.txt")

   message(STATUS "We're going to target a Raspberry PI!!")

   set(__TARGET_SYSTEM_ARCHITECTURE "aarch64")

   message(STATUS "Currently chosen __TARGET_SYSTEM_ARCHITECTURE is ${__TARGET_SYSTEM_ARCHITECTURE}")

   if(NOT "${__SYSTEM_ARCHITECTURE}" STREQUAL "aarch64")

      message(STATUS "Currently chosen __TARGET_SYSTEM_ARCHITECTURE is different from __SYSTEM_ARCHITECTURE")

      include("operating_system/aarch64-linux-toolchain.cmake")

   endif()

else()

   set(__TARGET_SYSTEM_ARCHITECTURE ${__SYSTEM_ARCHITECTURE})


endif()

message(STATUS "__TARGET_SYSTEM_ARCHITECTURE is ${__TARGET_SYSTEM_ARCHITECTURE}")

#execute_process(COMMAND uname -m OUTPUT_VARIABLE __SYSTEM_ARCHITECTURE)
#string(STRIP ${__SYSTEM_ARCHITECTURE} __SYSTEM_ARCHITECTURE)
#message(STATUS "__SYSTEM_ARCHITECTURE is ${__SYSTEM_ARCHITECTURE}")
#
#
#if(EXISTS "${CMAKE_SOURCE_DIR}/raspberrypios.txt")
#
#   message(STATUS "We're going to target a Raspberry PI!!")
#
#   set(__TARGET_SYSTEM_ARCHITECTURE "aarch64")
#
#   message(STATUS "Currently chosen __TARGET_SYSTEM_ARCHITECTURE is ${__TARGET_SYSTEM_ARCHITECTURE}")
#
#   if(NOT "${__SYSTEM_ARCHITECTURE}" STREQUAL "aarch64")
#
#      message(STATUS "Currently chosen __TARGET_SYSTEM_ARCHITECTURE is different from __SYSTEM_ARCHITECTURE")
#
#      include("operating_system/aarch64-linux-toolchain.cmake")
#
#   endif()
#
#else()
#
#   set(__TARGET_SYSTEM_ARCHITECTURE ${__SYSTEM_ARCHITECTURE})
#
#
#endif()


if("${__TARGET_SYSTEM_ARCHITECTURE}" STREQUAL "amd64")

   set(TARGET_ARCH "x64")

elseif("${__TARGET_SYSTEM_ARCHITECTURE}" STREQUAL "x86_64")

   set(TARGET_ARCH "x64")

elseif("${__TARGET_SYSTEM_ARCHITECTURE}" STREQUAL "aarch64")

   set(TARGET_ARCH "aarch64")

endif()

execute_process(COMMAND lsb_release -is OUTPUT_VARIABLE __OPERATING_SYSTEM)
string(STRIP ${__OPERATING_SYSTEM} __OPERATING_SYSTEM)
string(TOLOWER ${__OPERATING_SYSTEM} __OPERATING_SYSTEM)
message(STATUS "__OPERATING_SYSTEM is ${__OPERATING_SYSTEM}")



