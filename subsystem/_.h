// Into tightvnc sources by Camilo on 2026-02-10 <3ThomasBorregaardSorensen!!
#pragma once



#include "acme/_.h"


#if defined(_subsystem_project)
#define CLASS_DECL_SUBSYSTEM  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_SUBSYSTEM  CLASS_DECL_IMPORT
#endif



namespace subsystem
{


   class Registry;

   class RegistryKey;

   class string_table;

   class resource_loader;

   class subsystem;

   class Shell;

   using LogWriter = ::particle;

   class File;

   class FileInterface;

   class SecurityIdentifier;

   class SecurityIdentifierInterface;

   class SecurityAttributes;

   class SecurityAttributesInterface;

   class SecurityDescriptor;

   class SecurityDescriptorInterface;

   class StringParser;

   class ProcessHandle;

   class ProcessHandleInterface;

   class ProcessCommandLine;

   class ProcessCommandLineInterface;

   class Screen;

   class ScreenInterface;

   class SocketIPv4;

   class SocketIPv4Interface;

   class SocketAddressIPv4;

   class SocketAddressIPv4Interface;

   class SocketStream;

   class SystemInformation;

   class SystemInformationInterface;

   class DesktopSelector;

   class DesktopSelectorInterface;

   class NamedPipe;

   class NamedPipeInterface;

   class PipeClient;

   class PipeClientInterface;

} // namespace subsystem


namespace innate_subsystem
{


   struct PixelFormat;


} // namespace innate_subsystem


//#include "acme/input_output/_.h"
#include "subsystem/thread/_.h"


