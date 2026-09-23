# Created by camilo on 2023-02 <3ThomasBorregaardSorensen!!
# default configuration
message(STATUS "source/app/_.cmake")
set(WITH_AUDIO FALSE)
set(INCLUDE_AUDIO FALSE)
set(INCLUDE_ICONV FALSE)
set(INCLUDE_IDN FALSE)
set(INCLUDE_DRAW2D_CAIRO FALSE)
set(INCLUDE_FREETYPE FALSE)
set(USE_PORT_FREEIMAGE FALSE)
set(INCLUDE_IMAGING_FREEIMAGE FALSE)
set(INCLUDE_FREEIMAGE FALSE)
set(INCLUDE_OPENGL FALSE)
set(INCLUDE_VULKAN FALSE)
set(INCLUDE_DIRECTX11 FALSE)
set(INCLUDE_DIRECTX12 FALSE)
set(INCLUDE_DIRECT2D FALSE)
set(INCLUDE_GPU FALSE)
set(INCLUDE_OPENGL FALSE)
set(HAS_SYSTEM_UNAC FALSE)
set(HAS_APP_VERIWELL FALSE)
set(USE_SYSTEM_JPEG TRUE)
#set(HAS_AUDIO_SYSTEM FALSE)
set(CURL_NANO_HTTP FALSE)
set(FREEBSD FALSE)
set(OPENBSD FALSE)
set(NETBSD FALSE)
set(DARWIN FALSE)
set(__BSD__ FALSE)
set(LINUX FALSE)
set(__APPLE__ FALSE)
set(APPLE FALSE)
set(SOLARIS FALSE)
set(MACOS FALSE)
set(SUSE FALSE)
set(FREEBSD FALSE)
set(NETBSD FALSE)
set(OPENBSD FALSE)
set(UBUNTU FALSE)
set(DEBIAN FALSE)
set(__ANDROID__ FALSE)
set(WIN32 FALSE)
set(UWP FALSE)
set(ENABLE_SUBSYSTEM FALSE)
set(HAS_NO_APPINDICATOR FALSE)
if(!WITH_X11_OPERATING_AMBIENT)
set(WITH_X11_OPERATING_AMBIENT FALSE)
endif()
#set(INCLUDE_IMAGING_FREEIMAGE FALSE)
#set(WIN32 FALSE)
#set(UWP FALSE)


set(CMAKE_CXX_STANDARD 20)

if(DEFINED ENV{HOME})
   set(HOME_DIR $ENV{HOME})
elseif(DEFINED ENV{USERPROFILE})
   set(HOME_DIR $ENV{USERPROFILE})
else()
   message(FATAL_ERROR "Cannot determine home directory")
endif()

message(STATUS "HOME_DIR is ${HOME_DIR}")

message(STATUS "CMAKE_SYSTEM_PROCESSOR is ${CMAKE_SYSTEM_PROCESSOR}")

if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
   message(STATUS "Target system is x86 or x86_64 architecture.")
   # You can set a variable or perform specific actions here
   set(IS_X86_ARCH TRUE)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "(aarch64)")
   message(STATUS "Target system is aarch64 architecture.")
   # You can set a variable or perform specific actions here
   set(IS_AARCH64_ARCH TRUE)
else()
   message(STATUS "Target system is not x86 or x86_64 or aarch64 architecture.")
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
set(APPLICATION_BUILD_HELPER_BINARY "${HOME_DIR}/code/operating_system/tool/bin/application_build_helper")


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

   message(STATUS "GNU Compiler")

   string(APPEND CMAKE_CXX_FLAGS "-fPIC -fexceptions -fnon-call-exceptions -frtti")

   #set(EXTRA_CXX_TARGET_COMPILER_OPTIONS "-ansi")

else()

   #set(EXTRA_CXX_TARGET_COMPILER_OPTIONS "")

endif ()




include_directories(${WORKSPACE_FOLDER})
include_directories(${HOME_DIR}/__config)
include_directories(${WORKSPACE_FOLDER}/source)
include_directories(${WORKSPACE_FOLDER}/source/app)
include_directories(${WORKSPACE_FOLDER}/source/app/include)
include_directories(${WORKSPACE_FOLDER}/source/app/_include)
include_directories(${WORKSPACE_FOLDER}/source/include)
include_directories(${WORKSPACE_FOLDER}/port/_)
if (NOT ${HAS_SYSTEM_UNAC})
   include_directories(${WORKSPACE_FOLDER}/port/base/unac/include)
endif ()
include_directories(${WORKSPACE_FOLDER}/port/include)
include_directories(${WORKSPACE_FOLDER}/operating_system)



message(STATUS "going to include \"operating_system/__.cmake\"")
include(operating_system/__.cmake)


if(__ANDROID__)
   set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
endif()

project(android-build-all C CXX ASM)

option(CA2_ENABLE_HWASAN "Instrument Android ARM64 native code with HWAddressSanitizer" OFF)
if(CA2_ENABLE_HWASAN)
   if(NOT __ANDROID__ OR NOT ANDROID_ABI STREQUAL "arm64-v8a")
      message(FATAL_ERROR "CA2_ENABLE_HWASAN requires Android arm64-v8a")
   endif()
   if(NOT CMAKE_C_COMPILER_ID STREQUAL "Clang" OR NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      message(FATAL_ERROR "CA2_ENABLE_HWASAN requires the Android NDK Clang compilers")
   endif()
   if(NOT ANDROID_STL STREQUAL "c++_shared")
      message(FATAL_ERROR "CA2_ENABLE_HWASAN requires -DANDROID_STL=c++_shared")
   endif()
   # Set before including the project tree so all native subdirectories inherit these.
   add_compile_options("$<$<COMPILE_LANGUAGE:C,CXX>:-fsanitize=hwaddress>"
      "$<$<COMPILE_LANGUAGE:C,CXX>:-fno-omit-frame-pointer>"
      "$<$<COMPILE_LANGUAGE:C,CXX>:-g>")
   add_link_options(-fsanitize=hwaddress)
   message(STATUS "ca2: HWAddressSanitizer enabled (run with LD_HWASAN=1 on Android 14+)")
endif()

if(__ANDROID__ AND DEFINED ANDROID_ABI)
   foreach(_android_storage_root_candidate
      "${CMAKE_CURRENT_LIST_DIR}/../../../../../operating_system/storage-android"
      "${CMAKE_CURRENT_LIST_DIR}/../../operating_system/storage-android")
      if(EXISTS "${_android_storage_root_candidate}")
         get_filename_component(_android_storage_root "${_android_storage_root_candidate}" ABSOLUTE)
         break()
      endif()
   endforeach()

   if(_android_storage_root)
      set(_android_storage_library_dir "${_android_storage_root}/${ANDROID_ABI}/library")
      set(_android_storage_pkg_config_dir "${_android_storage_library_dir}/pkgconfig")
   endif()

   if(EXISTS "${_android_storage_library_dir}")
      link_directories("${_android_storage_library_dir}")
   endif()

   if(EXISTS "${_android_storage_pkg_config_dir}")
      if(DEFINED ENV{PKG_CONFIG_PATH} AND NOT "$ENV{PKG_CONFIG_PATH}" STREQUAL "")
         set(ENV{PKG_CONFIG_PATH} "${_android_storage_pkg_config_dir};$ENV{PKG_CONFIG_PATH}")
      else()
         set(ENV{PKG_CONFIG_PATH} "${_android_storage_pkg_config_dir}")
      endif()
   endif()
endif()



message(STATUS "going to include \"port/__.cmake\"")
include(port/__.cmake)


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


#add_subdirectory(source/app/launch)
#add_subdirectory(source/app/store)



