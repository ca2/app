// Into tightvnc sources by Camilo on 2026-02-10 <3ThomasBorregaardSorensen!!
#pragma once



#include "acme/_.h"


#if defined(_subsystem_project)
#define CLASS_DECL_SUBSYSTEM  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_SUBSYSTEM  CLASS_DECL_IMPORT
#endif



//namespace subsystem
//{

   struct interface_t
   {
   };

   // CLASS_DECL_SUBSYSTEM void subsystem_factory(::factory::factory * pfactory);


   enum enum_particle
   {

      e_particle_none,
      e_particle_interface,
      e_particle_implementation,

   };

   class Particle;

//   template<typename PARTICLE_INTERFACE, typename BASE = particle_base>
//   class particle_interface;

   template<typename PARTICLE_INTERFACE>
   class Composite;
   //template<typename PARTICLE_INTERFACE>
   //class composite;
   template<typename PARTICLE_INTERFACE, typename BASE = Particle>
   class Aggregate;

   template<typename PARTICLE_INTERFACE, typename BASE = Particle>
   class Implementation;


// node
namespace subsystem
{


   class DynamicLibrary;
   class DynamicLibraryInterface;

}


namespace subsystem
{


   class Registry;

   class RegistryKey;

   class StringTable;

   class ResourceLoader;

   class subsystem;

   class Shell;

   using LogWriter = ::particle;

   class File;

    class FileInterface;

    class Node;

   //using FileInterface = particle_interface <FileInterface>;

   class SecurityIdentifier;

    class SecurityIdentifierInterface;

   //using SecurityIdentifierInterface = particle_interface <SecurityIdentifierInterface>;

   class SecurityAttributes;

    class SecurityAttributesInterface;

   //using SecurityAttributesInterface = particle_interface <SecurityAttributesInterface>;

   class SecurityDescriptor;

    class SecurityDescriptorInterface;

   //using SecurityDescriptorInterface = particle_interface <SecurityDescriptorInterface>;

   class StringParser;

   class ProcessHandle;

    class ProcessHandleInterface;

   //using ProcessHandleInterface = particle_interface <ProcessHandleInterface>;

   class ProcessCommandLine;

    class ProcessCommandLineInterface;

   //using ProcessCommandLineInterface = particle_interface <ProcessCommandLineInterface>;

   class Screen;

    class ScreenInterface;

   //using ScreenInterface = particle_interface <ScreenInterface>;

   class SocketIPv4;

    class SocketIPv4Interface;

   //using SocketIPv4Interface = particle_interface <SocketIPv4Interface>;

   class SocketAddressIPv4;

    class SocketAddressIPv4Interface;

   //using SocketAddressIPv4Interface = particle_interface <SocketAddressIPv4Interface>;

   class SocketStream;

   class Sockets;

   class SystemInformation;

    class SystemInformationInterface;

   //using SystemInformationInterface = particle_interface <SystemInformationInterface>;

   class DesktopSelector;

    class DesktopSelectorInterface;

   //using DesktopSelectorInterface = particle_interface <DesktopSelectorInterface>;

   class NamedPipe;

    class NamedPipeInterface;

   //class NamedPipeInterface;

   class PipeClient;

    class PipeClientInterface;

   //using PipeClientInterface = particle_interface <PipeClientInterface>;

    class CommandLineArguments;

    class OperatingSystem;

    class SessionChangesWatcher;

    class Workstation;

    class WorkstationInterface;

    class Clipboard2;

    class ClipboardListener;

   class ZombieKiller;

   class WindowMessageHandler;

} // namespace subsystem


namespace innate_subsystem
{


   struct PixelFormat;


} // namespace innate_subsystem


//#include "acme/input_output/_.h"
#include "subsystem/thread/_.h"



#ifdef WINDOWS

namespace subsystem_windows
{
   class MessageWindow;
   
}


#endif



