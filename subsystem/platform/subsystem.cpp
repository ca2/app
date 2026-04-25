//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "StringParser.h"
#include "StringTable.h"
#include "node/Workstation.h"
#include "ResourceLoader.h"
#include "acme/platform/registry.h"
#include "node/OperatingSystem.h"
#include "node/Shell.h"
#include "node/PipeClient.h"
#include "Registry.h"
#include "thread/DesktopSelector.h"
#include "thread/SessionChangesWatcher.h"
#include "acme/exception/interface_only.h"
#include "node/SystemInformation.h"
#include "thread/ZombieKiller.h"
#include "socket/Sockets.h"
#include "CommandLineArguments.h"
#include "node/CurrentConsoleProcess.h"


namespace subsystem
{


   ::subsystem::subsystem *subsystem::s_p = nullptr;


   subsystem::subsystem()
   {

      s_p = this;

   }


   subsystem::~subsystem()
   {


   }


   ::subsystem::StringParser & subsystem::StringParser()
   {

      if (!m_pstringparser)
      {

         construct_newø(m_pstringparser);

      }

      return *m_pstringparser;

   }


   ::subsystem::StringTable & subsystem::StringTable()
   {

      if (!m_pstringtable)
      {

         constructø(m_pstringtable);

      }

      return *m_pstringtable;

   }



   ::subsystem::ResourceLoader * subsystem::ResourceLoader()
   {

      if (!m_presourceloader)
      {

         constructø(m_presourceloader);

      }

      return m_presourceloader;

   }


   ::subsystem::OperatingSystem& subsystem::OperatingSystem()
   {

      if (!m_poperatingsystem)
      {

         constructø(m_poperatingsystem);

      }

      return *m_poperatingsystem;

   }


   ::subsystem::Registry & subsystem::Registry()
   {

      if (!m_pregistry)
      {

         construct_newø(m_pregistry);

      }

      return *m_pregistry;

   }


   ::subsystem::Shell & subsystem::Shell()
   {

      if (!m_pshell)
      {

         constructø(m_pshell);

      }

      return *m_pshell;

   }


   ::subsystem::WorkstationInterface & subsystem::Workstation()
   {

      if (!m_pworkstation)
      {


         constructø(m_pworkstation);
      }

      return *m_pworkstation;
   }




   ::subsystem::SystemInformationInterface & subsystem::SystemInformation()
   {

      if (!m_psysteminformation   )
      {


         constructø(m_psysteminformation);

      }

      return *m_psysteminformation;

   }


   ::subsystem::DesktopSelectorInterface & subsystem::DesktopSelector()
   {

      if (!m_pdesktopselector   )
      {


         constructø(m_pdesktopselector);

      }

      return *m_pdesktopselector;

   }


   ::subsystem::PipeClientInterface & subsystem::PipeClient()
   {

      if (!m_ppipeclient   )
      {


         constructø(m_ppipeclient);

      }

      return *m_ppipeclient;

   }

   //void subsystem::initializeCommandLineArguments(CommandLineArguments* pcommandlinearguments,
   //                                               const ::scoped_string &scopedstrCommandLine)
   //{

   //   throw ::interface_only();

   //}

   ::pointer < ::subsystem::CurrentConsoleProcess> subsystem::createCurrentConsoleProcess(
   ::subsystem::LogWriter *plogwriter,
   bool bConnectRdpSession,
   const ::scoped_string & scopedstrPath,
   const ::scoped_string & scopedstrArgs)
   {

      auto pcurrentconsoleprocess = createø<::subsystem::CurrentConsoleProcess>();

      pcurrentconsoleprocess->initialize_current_console_process(plogwriter, bConnectRdpSession, scopedstrPath, scopedstrArgs);

      return pcurrentconsoleprocess;

   }



   void subsystem::startSockets()
   {

      if (!Sockets().m_bIsStarted)
      {

         Sockets().startSockets();

      }

   }


   void subsystem::cleanupSockets()
   {

      if (m_psockets)
      {

         if (Sockets().m_bIsStarted)
         {

            Sockets().cleanupSockets();

         }

      }

   }

   
   memsize subsystem::getCurrentMemoryUsage()
   {

      throw ::interface_only();

      return 0;

   }


   pointer<CommandLineArguments> subsystem::getCurrentProcessCommandLineArguments()
   {

      throw ::interface_only();

      return {};
      // auto pcommandlinearguments = create_newø<CommandLineArguments>();

      // pcommandlinearguments->ini, scopedstrCommandLine);

      // return pcommandlinearguments;
   }


   pointer<CommandLineArguments> subsystem::getCommandLineArguments(const ::scoped_string &scopedstrCommandLine)
   {

      throw ::interface_only();

      return {};
      //auto pcommandlinearguments = create_newø<CommandLineArguments>();

      //pcommandlinearguments->ini, scopedstrCommandLine);

      //return pcommandlinearguments;

   }

   
   pointer<::subsystem::FileInterface> subsystem::fileFrom_HANDLE(void* pHANDLE)
   {

      throw ::interface_only();

      return {};


   }


   ::pointer < ::subsystem::SecurityIdentifier > subsystem::createSidFromString(const ::scoped_string & scopedstr)
   {

      return nullptr;

   }


   int subsystem::message_box(
   const ::user_interaction_sink & userinteractionsink,
   const ::scoped_string & scopedstrMessage,
   const ::scoped_string & scopedstrCaption,
   unsigned int uType)
   {

      throw ::interface_only();

      return 0;
   }


   bool subsystem::EncryptData(const ::string& input, ::memory & output)
   {

      throw ::interface_only();

      return false;

   }


   bool subsystem::DecryptData(const memory & input, ::string& output)
   {

      throw ::interface_only();

      return false;

   }


   int subsystem::get_last_socket_error()
   {

      return -1;

   }


   string subsystem::get_socket_error_message_text(int iError)
   {

      return {};

   }


   ::pointer < ::subsystem::SocketAddressIPv4Interface > subsystem::resolve_ip4_address(const ::scoped_string & scopedstrHost, unsigned short port)
   {

      return {};

   }


   unsigned int subsystem::internet_address4(const ::scoped_string& scopedstr)
   {

      throw ::interface_only();

      return 0;

   }


   ::string subsystem::internet_address4_as_string(unsigned int u)
   {

      throw ::interface_only();

      return {};

   }


   unsigned int subsystem::host_to_network_long(unsigned int u)
   {

      throw ::interface_only();

      return 0;
   }

   
   unsigned int subsystem::network_to_host_long(unsigned int u)
   {

      throw ::interface_only();

      return 0;

   }

   void subsystem::start_SessionChangesWatcher(const ::procedure& procedureSessionChanged,
                                               ::subsystem::LogWriter *plogwriter)
   {

      if (m_psessionchangeswatcher)
      {

         throw "Currently only one is supported?!?!?";

      }

      constructø(m_psessionchangeswatcher);

      m_psessionchangeswatcher->start_SessionChangesWatcher(procedureSessionChanged, plogwriter);

   }

   
   ::string subsystem::toString(const ::earth::time& time)
   {

      throw ::interface_only();

      return {};

   }


   string subsystem::getLocalIpAddressString()
   {

      throw ::interface_only();

      return {};


   }


   int subsystem::get_LOADER_CLOSE_CODE()
   {

      throw ::interface_only();

      return -1;

   }


   int subsystem::get_SPEC_IPC_CODE()
   {

      throw ::interface_only();

      return -1;

   }


   // RegisterWindowMessage("TVN.HOOK.LOADER.CLOSE.CODE");
   // const unsigned int HookDefinitions::SPEC_IPC_CODE =
   // RegisterWindowMessage("TVN.HOOK.MESSAGE.CODE");


   ZombieKiller & subsystem::ZombieKiller()
   {

      if (!m_pzombiekiller)
      {

         constructø(m_pzombiekiller);

      }

      return *m_pzombiekiller;

   }


   ::subsystem::Sockets &subsystem::Sockets()
   {

      if (!m_psockets)
      {

         constructø(m_psockets);

      }

      return *m_psockets;

   }


}//namespace subsystem
