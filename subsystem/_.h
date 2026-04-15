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

   class particle_base;

   template<typename PARTICLE_INTERFACE, typename BASE = particle_base>
   class particle_interface;

   template<typename PARTICLE_INTERFACE>
   class composite;
   //template<typename PARTICLE_INTERFACE>
   //class composite;
   template<typename PARTICLE_INTERFACE, typename BASE = particle_base>
   class aggregate;

   template<typename PARTICLE_INTERFACE, typename BASE = particle_base>
   class implementation;

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

    class FileSlice;

   using FileInterface = particle_interface <FileSlice>;

   class SecurityIdentifier;

    class SecurityIdentifierSlice;

   using SecurityIdentifierInterface = particle_interface <SecurityIdentifierSlice>;

   class SecurityAttributes;

    class SecurityAttributesSlice;

   using SecurityAttributesInterface = particle_interface <SecurityAttributesSlice>;

   class SecurityDescriptor;

    class SecurityDescriptorSlice;

   using SecurityDescriptorInterface = particle_interface <SecurityDescriptorSlice>;

   class StringParser;

   class ProcessHandle;

    class ProcessHandleSlice;

   using ProcessHandleInterface = particle_interface <ProcessHandleSlice>;

   class ProcessCommandLine;

    class ProcessCommandLineSlice;

   using ProcessCommandLineInterface = particle_interface <ProcessCommandLineSlice>;

   class Screen;

    class ScreenSlice;

   using ScreenInterface = particle_interface <ScreenSlice>;

   class SocketIPv4;

    class SocketIPv4Slice;

   using SocketIPv4Interface = particle_interface <SocketIPv4Slice>;

   class SocketAddressIPv4;

    class SocketAddressIPv4Slice;

   using SocketAddressIPv4Interface = particle_interface <SocketAddressIPv4Slice>;

   class SocketStream;

   class SystemInformation;

    class SystemInformationSlice;

   using SystemInformationInterface = particle_interface <SystemInformationSlice>;

   class DesktopSelector;

    class DesktopSelectorSlice;

   using DesktopSelectorInterface = particle_interface <DesktopSelectorSlice>;

   class NamedPipe;

    class NamedPipeSlice;

   //class NamedPipeInterface;

   class PipeClient;

    class PipeClientSlice;

   using PipeClientInterface = particle_interface <PipeClientSlice>;

} // namespace subsystem


namespace innate_subsystem
{


   struct PixelFormat;


} // namespace innate_subsystem


//#include "acme/input_output/_.h"
#include "subsystem/thread/_.h"


