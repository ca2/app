cmake_minimum_required(VERSION 3.16)
project(subsystem CXX)


list(APPEND library_source
   framebuffer/PixelFormat.cpp
   framebuffer/PixelFormat.h
   framebuffer/StandardPixelFormatFactory.cpp
   framebuffer/StandardPixelFormatFactory.h
#   io/_.cpp
#   io/_.h
#   #io/_____debug.xcconfig
#   #io/_____release.xcconfig
#   #io/aaa_framework.cpp
#   #io/aaa_framework.h
#   #io/aaa_io_exception.h
#   io/BufferedInputStream.cpp
#   io/BufferedInputStream.h
#   io/BufferedOutputStream.cpp
#   io/BufferedOutputStream.h
#   io/ByteArrayInputStream.cpp
#   io/ByteArrayInputStream.h
#   io/ByteArrayOutputStream.cpp
#   io/ByteArrayOutputStream.h
#   io/Channel.cpp
#   io/Channel.h
#   #io/CMakeLists.txt
#   io/DataCopy.cpp
#   io/DataCopy.h
#   io/DataInputStream.cpp
#   io/DataInputStream.h
#   io/DataOutputStream.cpp
#   io/DataOutputStream.h
#   io/InputStream.cpp
#   io/InputStream.h
#   io/io_exception.cpp
#   #io/io_lib.vcproj
#   #io/matter.txt
#   io/OutputStream.cpp
#   io/OutputStream.h
   node/OperatingSystemHookListener.cpp
   node/security/SecurityDescriptor.cpp
   node/security/SecurityDescriptor.h
   node/security/SecurityIdentifier.cpp
   node/security/SecurityIdentifier.h
   node/security/SecurityAttributes.cpp
   node/security/SecurityAttributes.h
   #node/SystemException.cpp
   #node/SystemException.h
   node/AnonymousPipe.cpp
   node/AnonymousPipe.h
   node/AnonymousPipeFactory.cpp
   node/AnonymousPipeFactory.h
   node/ApplicationCrashEvents.h
   node/AutoImpersonator.cpp
   node/AutoImpersonator.h
   node/Clipboard.cpp
   node/Clipboard.h
   #node/CMakeLists.txt
   node/CrashHook.cpp
   node/CrashHook.h
   node/CurrentConsoleProcess.cpp
   node/CurrentConsoleProcess.h
   node/Cursor.cpp
   node/Cursor.h
   node/Displays.cpp
   node/Displays.h
   node/DynamicLibrary.cpp
   node/DynamicLibrary.h
   node/EmulatedAnonymousPipeFactory.cpp
   node/EmulatedAnonymousPipeFactory.h
   node/File.cpp
   node/File.h
   node/Impersonator.cpp
   node/Impersonator.h
   node/InputInjector.cpp
   node/InputInjector.h
   node/Keyboard.cpp
   node/Keyboard.h
   node/LocalOperatingSystemApplication.cpp
   node/LocalOperatingSystemApplication.h
   node/matter.txt
   node/NamedPipe.cpp
   node/NamedPipe.h
   node/OperatingSystem.cpp
   node/OperatingSystem.h
   node/OperatingSystemApplication.cpp
   node/OperatingSystemApplication.h
   node/OperatingSystemHook.cpp
   node/OperatingSystemHook.h
   node/OperatingSystemHookListener.cpp
   node/OperatingSystemHookListener.h
   node/ParentProcess.cpp
   node/Pipe.cpp
   node/Pipe.h
   node/PipeClient.cpp
   node/PipeClient.h
   node/PipeImpersonatedThread.cpp
   node/PipeImpersonatedThread.h
   node/PipeServer.cpp
   node/PipeServer.h
   node/Process.cpp
   node/Process.h
   node/ProcessCommandLine.cpp
   node/ProcessCommandLine.h
   node/ProcessHandle.cpp
   node/ProcessHandle.h
   node/remoting_win_system.vcxproj
   node/remoting_win_system.vcxproj.filters
   node/remoting_win_system.vcxproj.user
   node/resource.h
   node/Screen.cpp
   node/Screen.h
   #node/SecurityDescriptor.cpp
   #node/SecurityIdentifier.cpp
   node/Service.cpp
   node/Service.h
   node/ServiceControlManagerClient.cpp
   node/ServiceControlManagerClient.h
   node/SharedMemory.cpp
   node/SharedMemory.h
   node/Shell.cpp
   node/Shell.h
   #node/string_table.cpp
   #node/string_table.h
   #node/StringStorage.cpp
   node/SystemException.cpp
   node/SystemException.h
   node/SystemInformation.cpp
   node/SystemInformation.h
   node/UipiControl.cpp
   node/UipiControl.h
   node/VersionInfo.cpp
   node/VersionInfo.h
   node/win_system.vcproj
   #node/WinCommandLineArgs.cpp
   #node/WinCommandLineArgs.h
   node/WindowsEvent.cpp
   node/WindowsEvent.h
   node/WindowsEventEx.cpp
   node/WindowsEventEx.h
   #node/WinHandles.cpp
   #node/WinHandles.h
   #node/WinHooks.cpp
   #node/WinHooks.h
   #node/WinProcessCommandLine.cpp
   #node/WinProcessCommandLine.h
   #node/WinStaLibrary.cpp
   #node/WinStaLibrary.h
   #node/WinTimeMillis.cpp
   #node/WinTimeMillis.h
   node/Workstation.cpp
   node/Workstation.h
   #node/WsaStartup.cpp
   #node/WsaStartup.h
   #node/WTS.cpp
   #node/WTS.h
   #   _____debug.xcconfig
   #   _____release.xcconfig
   #   aaa_Environment.cpp
   #   aaa_Environment.h
   #   aaa_framework.cpp
   #   aaa_framework.h
   #   aaa_StringStorage.h
   #platform/AnonymousPipe.cpp
   #platform/AnonymousPipe.h
   #platform/AnonymousPipeFactory.cpp
   #platform/AnonymousPipeFactory.h
   #platform/ApplicationCrashEvents.h
   #platform/AutoImpersonator.cpp
   #platform/AutoImpersonator.h
   platform/CommandLineArguments.cpp
   platform/CommandLineArguments.h
   #platform/CurrentConsoleProcess.cpp
   #platform/CurrentConsoleProcess.h
   platform/Deflater.cpp
   platform/Deflater.h
   platform/DemandTimer.cpp
   platform/DemandTimer.h
   #platform/DynamicLibrary.cpp
   #platform/DynamicLibrary.h
   #platform/EmulatedAnonymousPipeFactory.cpp
   #platform/EmulatedAnonymousPipeFactory.h
   platform/Exception.cpp
   platform/Exception.h
   #platform/HookEventListener.h
   #platform/Impersonator.cpp
   #platform/Impersonator.h
   platform/Inflater.cpp
   platform/Inflater.h
   #platform/InputInjector.cpp
   #platform/InputInjector.h
   #platform/Keyboard.cpp
   #platform/Keyboard.h
   platform/Keymap.cpp
   platform/Keymap.h
   #platform/LocalWindowsApplication.cpp
   #platform/LocalWindowsApplication.h
   #platform/matter.txt
   #platform/NamedPipe.cpp
   #platform/NamedPipe.h
   #platform/ParentProcess.cpp
   #platform/ParentProcess.h
   platform/Particle.cpp
   platform/Particle.h
   #platform/Pipe.cpp
   #platform/Pipe.h
   #platform/PipeClient.cpp
   #platform/PipeClient.h
   #platform/PipeImpersonatedThread.cpp
   #platform/PipeImpersonatedThread.h
   #platform/PipeServer.cpp
   #platform/PipeServer.h
   #platform/Process.cpp
   #platform/Process.h
   #platform/ProcessHandle.cpp
   #platform/ProcessHandle.h
   platform/Registry.cpp
   platform/Registry.h
   platform/RegistryKey.cpp
   platform/RegistryKey.h
   #platform/resource.h
   platform/ResourceLoader.cpp
   platform/ResourceLoader.h
   #platform/SCMClient.cpp
   #platform/SCMClient.h
   #platform/Screen.cpp
   #platform/Screen.h
   #platform/SecurityAttributes.cpp
   #platform/SecurityAttributes.h
   #platform/SecurityDescriptor.cpp
   #platform/SecurityIdentifier.cpp
   #platform/Service.cpp
   #platform/Service.h
   #platform/SharedMemory.cpp
   #platform/SharedMemory.h
   #platform/Shell.cpp
   #platform/Shell.h
   platform/Singleton.h
   platform/StringTable.cpp
   platform/StringTable.h
   platform/StringParser.cpp
   platform/StringParser.h
   #platform/StringStorage.cpp
   platform/subsystem.h
   platform/subsystem.cpp
   #platform/SystemInformation.cpp
   #platform/SystemInformation.h
   #platform/UipiControl.cpp
   #platform/UipiControl.h
   #platform/VersionInfo.cpp
   #platform/VersionInfo.h
   #platform/win_system.vcproj
   #platform/WinClipboard.cpp
   #platform/WinClipboard.h
   #platform/WinCommandLineArgs.cpp
   #platform/WinCommandLineArgs.h
   #platform/WinCursor.cpp
   #platform/WinCursor.h
   platform/WindowMessageHandler.cpp
   platform/WindowMessageHandler.h
   #platform/WindowsApplication.cpp
   #platform/WindowsApplication.h
   #platform/WindowsDisplays.cpp
   #platform/WindowsDisplays.h
   #platform/WindowsEvent.cpp
   #platform/WindowsEvent.h
   #platform/WindowsEventEx.cpp
   #platform/WindowsEventEx.h
   #platform/WinHandles.cpp
   #platform/WinHandles.h
   #platform/WinHooks.cpp
   #platform/WinHooks.h
   #platform/WinProcessCommandLine.cpp
   #platform/WinProcessCommandLine.h
   #platform/WinStaLibrary.cpp
   #platform/WinStaLibrary.h
   #platform/WinTimeMillis.cpp
   #platform/WinTimeMillis.h
   #platform/Workstation.cpp
   #platform/Workstation.h
   #platform/WsaStartup.cpp
   #platform/WsaStartup.h
   #platform/WTS.cpp
   #platform/WTS.h
   platform/ZLibBase.cpp
   platform/ZLibBase.h
   platform/ZlibException.cpp
   platform/ZlibException.h
   socket/sockdefs.h
   socket/SocketAddressIPv4.cpp
   socket/SocketAddressIPv4.h
   socket/SocketException.cpp
   socket/SocketException.h
   socket/SocketIPv4.cpp
   socket/SocketIPv4.h
   socket/Sockets.cpp
   socket/Sockets.h
   socket/SocketStartup.cpp
   socket/SocketStartup.h
   socket/SocketStream.cpp
   socket/SocketStartup.h
   thread/_.cpp
   thread/_.h
   #thread/_____debug.xcconfig
   #thread/_____release.xcconfig
   #thread/aaa_framework.cpp
   #thread/aaa_framework.h
   #thread/aaa_ZombieKiller.cpp
   #thread/aaa_ZombieKiller.h
   thread/AutoLock.cpp
   thread/AutoLock.h
   #thread/CMakeLists.txt
   thread/DesktopSelector.cpp
   thread/DesktopSelector.h
   thread/GlobalMutex.cpp
   thread/GlobalMutex.h
   thread/GuiThread.cpp
   thread/GuiThread.h
   thread/LocalMutex.cpp
   thread/LocalMutex.h
   thread/Lockable.h
   #thread/matter.txt
   #thread/remoting_thread.vcxproj
   #thread/remoting_thread.vcxproj.filters
   #thread/remoting_thread.vcxproj.user
   #thread/resource.h
   thread/SessionChangesWatcher.cpp
   thread/SessionChangesWatcher.h
   thread/Thread.cpp
   thread/Thread.h
   thread/thread.vcproj
   thread/ThreadCollector.cpp
   thread/ThreadCollector.h
   thread/ZombieKiller.cpp
   thread/ZombieKiller.h
   _.cpp
   _.h
   _common_header.h
   framework.cpp
   framework.h
   )


list(APPEND library_references
   acme
   apex
   aqua
   aura
)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})




#if(${LINUX} OR ${__BSD__})


   #add_custom_command(
      #OUTPUT ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
      #COMMAND ${APPLICATION_BUILD_HELPER_BINARY} --prepare-application ${PROJECT_SOURCE_DIR}
      #COMMENT "Generating ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o"
   #)

   #target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

#endif()




if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if(${WIN32})


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} zlib)


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

   message(STATUS "(5) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})


endif ()


add_dependencies(${PROJECT_NAME} apex_${OPERATING_SYSTEM_NAME})
add_dependencies(${PROJECT_NAME} ${default_node})
add_dependencies(${PROJECT_NAME} ${default_draw2d})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)


#add_subdirectory(__implement)



