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


      ::pointer < ::subsystem::OperatingSystemApplicationInterface > m_papplicationSubsystem;
      ::hinstance                                        m_hinstanceResource = nullptr;
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
      virtual pointer<::subsystem::FileInterface> fileFrom_fd(::i32 fd);

      /**
       * Creates SID from sid string.
       * @return created SID.
       * @throws SystemException on fail.
       */
      virtual ::pointer < ::subsystem::SecurityIdentifier > createSidFromString(const ::scoped_string & scopedstr);


      virtual ::enum_dialog_result message_box(
         const ::user_interaction_sink & userinteractionsink,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         const ::user::e_message_box & emessagebox);


      virtual bool EncryptData(const ::string& input, ::memory & output);
      virtual bool DecryptData(const memory & input, ::string& output);


      virtual ::i32 get_last_socket_error();
      virtual ::string get_socket_error_message_text(::i32 iError);
      virtual ::pointer < ::subsystem::SocketAddressIPv4Interface > resolve_ip4_address(const ::scoped_string & scopedstrHost, ::u16 port);


      virtual ::u32 internet_address4(const ::scoped_string &scopedstr);
      virtual ::string internet_address4_as_string(::u32 u);
      virtual ::u32 host_to_network_long(::u32 u);
      virtual ::u32 network_to_host_long(::u32 u);

      virtual void start_SessionChangesWatcher(const ::procedure &procedureSessionChanged,
                                               ::subsystem::LogWriter *plogwriter);


      virtual ::string toString(const ::earth::time &time);



      // Should deprecate this function?!?!?
      virtual ::string getLocalIpAddressString();



      virtual ::i32 get_LOADER_CLOSE_CODE();
      virtual ::i32 get_SPEC_IPC_CODE();
      // RegisterWindowMessage("TVN.HOOK.LOADER.CLOSE.CODE");
      // const ::u32 HookDefinitions::SPEC_IPC_CODE =
      // RegisterWindowMessage("TVN.HOOK.MESSAGE.CODE");


   };



} // namespace subsystem



CLASS_DECL_SUBSYSTEM ::subsystem::subsystem & MainSubsystem();
