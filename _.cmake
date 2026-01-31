# Created by camilo on 2023-02 <3ThomasBorregaardSorensen!!
# default configuration
message(STATUS "source/app/_.cmake")
set(INCLUDE_AUDIO FALSE)
set(INCLUDE_ICONV FALSE)
set(INCLUDE_IDN FALSE)
set(INCLUDE_DRAW2D_CAIRO FALSE)
set(INCLUDE_FREETYPE FALSE)
set(USE_PORT_FREEIMAGE FALSE)
set(INCLUDE_IMAGING_FREEIMAGE FALSE)
set(INCLUDE_FREEIMAGE FALSE)
if(!INCLUDE_OPENGL)
set(INCLUDE_OPENGL FALSE)
endif()
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
set(ANDROID FALSE)
set(WIN32 FALSE)
set(UWP FALSE)
set(HAS_NO_APPINDICATOR FALSE)
if(!WITH_X11_OPERATING_AMBIENT)
set(WITH_X11_OPERATING_AMBIENT FALSE)
endif()
#set(INCLUDE_IMAGING_FREEIMAGE FALSE)
#set(WIN32 FALSE)
#set(UWP FALSE)


set(CMAKE_CXX_STANDARD 20)

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
set(APPLICATION_BUILD_HELPER_BINARY "$ENV{HOME}/code/operating_system/tool/bin/application_build_helper")


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

   message(STATUS "GNU Compiler")

   string(APPEND CMAKE_CXX_FLAGS "-fPIC -fexceptions -fnon-call-exceptions -frtti")

   #set(EXTRA_CXX_TARGET_COMPILER_OPTIONS "-ansi")

else()

   #set(EXTRA_CXX_TARGET_COMPILER_OPTIONS "")

endif ()




include_directories(${WORKSPACE_FOLDER})
include_directories($ENV{HOME}/__config)
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



