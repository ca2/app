//
// Created by camilo on 2026-04-05 03:03 <3ThomasBorregaardSørensen!!
//


// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/subsystem.h"
#include "acme/platform/user_interaction_sink.h"
#include "subsystem/platform/StringParser.h"


namespace subsystem
{


   class CLASS_DECL_SUBSYSTEM subsystem :
      virtual public ::platform::subsystem
   {
   public:


      ::hinstance                                        m_hinstanceResource = nullptr;
      static ::subsystem::subsystem *            s_p;
      ::pointer < ::subsystem::StringParser >     m_pstringparser;
      ::pointer < ::subsystem::StringTable >     m_pstringtable;
      ::pointer < ::subsystem::ResourceLoader >     m_presourceloader;
      ::pointer < ::subsystem::Registry >     m_pregistry;
      ::pointer < ::subsystem::Shell >     m_pshell;
      ::pointer<::subsystem::WorkstationInterface> m_pworkstation;
      ::pointer < ::subsystem::SystemInformationInterface > m_psysteminformation;
      ::pointer < ::subsystem::DesktopSelectorInterface > m_pdesktopselector;
      ::pointer < ::subsystem::PipeClientInterface > m_ppipeclient;
      ::pointer<::subsystem::OperatingSystem> m_poperatingsystem;
      ::pointer<::subsystem::SessionChangesWatcher> m_psessionchangeswatcher;
      ::pointer<::subsystem::ZombieKiller> m_pzombiekiller;
      ::pointer<::subsystem::Sockets> m_psockets;


      subsystem();
      ~subsystem() override;


      virtual ::subsystem::StringParser & StringParser();
      virtual ::subsystem::StringTable & StringTable();
      virtual ::subsystem::Registry & Registry();
      virtual ::subsystem::Shell & Shell();
      virtual ::subsystem::WorkstationInterface & Workstation();
      virtual ::subsystem::SystemInformationInterface & SystemInformation();
      virtual ::subsystem::DesktopSelectorInterface & DesktopSelector();
      virtual ::subsystem::PipeClientInterface & PipeClient();
      ::subsystem::ResourceLoader * ResourceLoader();
      ::subsystem::OperatingSystem & OperatingSystem();
      ::subsystem::ZombieKiller & ZombieKiller();
      ::subsystem::Sockets & Sockets();


      virtual ::pointer < ::subsystem::CurrentConsoleProcess> createCurrentConsoleProcess(
         ::subsystem::LogWriter *log,
         bool connectRdpSession,
         const ::scoped_string & scopedstrPath = {},
         const ::scoped_string & scopedstrArgs = {});


      //virtual void initializeCurrentProcessCommandLineArguments(
        // CommandLineArguments *pcommandlinearguments);

      //virtual void initializeCommandLineArguments(
        // CommandLineArguments *pcommandlinearguments, const ::scoped_string &scopedstrCommandLine);


      virtual void startSockets();
      virtual void cleanupSockets();

      virtual memsize getCurrentMemoryUsage();

      virtual pointer<CommandLineArguments> getCurrentProcessCommandLineArguments();

      virtual pointer<CommandLineArguments> getCommandLineArguments(const ::scoped_string &scopedstrCommandLine);

      virtual pointer<::subsystem::FileInterface> fileFrom_HANDLE(void *pHANDLE);

      /**
       * Creates SID from sid string.
       * @return created SID.
       * @throws SystemException on fail.
       */
      virtual ::pointer < ::subsystem::SecurityIdentifier > createSidFromString(const ::scoped_string & scopedstr);


      virtual int message_box(
         const ::user_interaction_sink & userinteractionsink,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         unsigned int uType);


      virtual bool EncryptData(const ::string& input, ::memory & output);
      virtual bool DecryptData(const memory & input, ::string& output);


      virtual int get_last_socket_error();
      virtual ::string get_socket_error_message_text(int iError);
      virtual ::pointer < ::subsystem::SocketAddressIPv4Interface > resolve_ip4_address(const ::scoped_string & scopedstrHost, unsigned short port);


      virtual unsigned int internet_address4(const ::scoped_string &scopedstr);
      virtual ::string internet_address4_as_string(unsigned int u);
      virtual unsigned int host_to_network_long(unsigned int u);
      virtual unsigned int network_to_host_long(unsigned int u);

      virtual void start_SessionChangesWatcher(const ::procedure &procedureSessionChanged,
                                               ::subsystem::LogWriter *plogwriter);


      virtual ::string toString(const ::earth::time &time);



      // Should deprecate this function?!?!?
      virtual ::string getLocalIpAddressString();



      virtual int get_LOADER_CLOSE_CODE();
      virtual int get_SPEC_IPC_CODE();
      // RegisterWindowMessage("TVN.HOOK.LOADER.CLOSE.CODE");
      // const unsigned int HookDefinitions::SPEC_IPC_CODE =
      // RegisterWindowMessage("TVN.HOOK.MESSAGE.CODE");


   };



} // namespace subsystem



inline ::subsystem::subsystem & MainSubsystem()
{

   if (!::subsystem::subsystem::s_p)
   {

      system()->MainSubsystem();

   }

   return *::subsystem::subsystem::s_p;

}

