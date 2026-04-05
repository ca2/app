cmake_minimum_required(VERSION 3.16)
project(remoting_win_system)


list(APPEND library_source
   security/SecurityDescriptor.cpp
   security/SecurityDescriptor.h
   security/SecurityIdentifier.cpp
   security/SecurityIdentifier.h
   framework.cpp
   framework.h
   _.cpp
   _.h
   AnonymousPipe.cpp
   AnonymousPipe.h
   AnonymousPipeFactory.h
   AnonymousPipeFactory.cpp
   ApplicationCrashEvents.h
   AutoImpersonator.cpp
   AutoImpersonator.h
   CtrlAltDelSimulator.cpp
   EmulatedAnonymousPipeFactory.h
   DibSection.h
   #Environment.h
   DibSection.cpp
   EmulatedAnonymousPipeFactory.cpp
   #Environment.cpp
   DynamicLibrary.h
   CurrentConsoleProcess.cpp
   DynamicLibrary.cpp
   CurrentConsoleProcess.h
   CtrlAltDelSimulator.h
   HookEventListener.h
   InputInjector.cpp
   Keyboard.cpp
   Impersonator.cpp
   LocalWindowsApplication.h
   Keyboard.h
   LocalWindowsApplication.cpp
   InputInjector.h
   Impersonator.h
   NamedPipe.cpp
   UipiControl.cpp
   PipeServer.h
   Registry.h
   ParentProcess.cpp
   Service.h
   Process.h
   Pipe.h
   ProcessHandle.cpp
   Screen.h
   SecurityAttributes.cpp
   PipeServer.cpp
   PipeImpersonatedThread.cpp
   SecurityAttributes.h
   Shell.h
   RegistryKey.h
   Service.cpp
   SharedMemory.cpp
   VersionInfo.cpp
   SCMClient.cpp
   NamedPipe.h
   Process.cpp
   SystemException.h
   SCMClient.h
   SystemInformation.h
   SharedMemory.h
   resource.h
   PipeClient.cpp
   PipeImpersonatedThread.h
   RegistryKey.cpp
   Pipe.cpp
   SystemException.cpp
   PipeClient.h
   ProcessHandle.h
   Screen.cpp
   Shell.cpp
   VersionInfo.h
   SystemInformation.cpp
   Registry.cpp
   ParentProcess.h
   UipiControl.h
   WinClipboard.cpp
   WinHooks.cpp
   WindowsDisplays.cpp
   WsaStartup.cpp
   WinHandles.cpp
   WindowsEventEx.cpp
   Workstation.h
   WinHandles.h
   WindowsDisplays.h
   WTS.h
   WsaStartup.h
   WindowsApplication.cpp
   WinTimeMillis.h
   WindowsApplication.h
   WindowsEvent.cpp
   WinProcessCommandLine.cpp
   WinHooks.h
   WinCommandLineArgs.cpp
   Workstation.cpp
   WinTimeMillis.cpp
   WinCursor.cpp
   WTS.cpp
   WinStaLibrary.cpp
   WinClipboard.h
   WinCommandLineArgs.h
   WinStaLibrary.h
   WindowsEvent.h
   WindowsEventEx.h
   WinProcessCommandLine.h
   WinCursor.h
)


list(APPEND library_references
   acme
)


list(APPEND library_include_directories
   ${CMAKE_CURRENT_SOURCE_DIR}/../..
   ${CMAKE_CURRENT_SOURCE_DIR}/..
   ${CMAKE_CURRENT_SOURCE_DIR}
)


add_library(${PROJECT_NAME} STATIC ${library_source}
   ../common/_.h
   ../common/remoting.cpp
   ../common/remoting.h)






#target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
#target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if(${WIN32})
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_compile_options(${PROJECT_NAME} PRIVATE "/bigobj")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})

elseif(${LINUX} OR ${__BSD__} OR ${ANDROID})
   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=$ORIGIN)
   #target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)

endif ()

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})

