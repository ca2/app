//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "StringParser.h"
#include "StringTable.h"
#include "ResourceLoader.h"
#include "acme/platform/registry.h"
#include "node/OperatingSystem.h"
#include "node/Shell.h"
#include "node/PipeClient.h"
#include "Registry.h"
#include "thread/DesktopSelector.h"
#include "acme/exception/interface_only.h"
#include "node/SystemInformation.h"


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


   ::subsystem::StringParser * subsystem::string_parser()
   {

      if (!m_pstringparser)
      {

         construct_newø(m_pstringparser);

      }

      return m_pstringparser;

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


   ::subsystem::Registry * subsystem::registry()
   {

      if (!m_pregistry)
      {

         construct_newø(m_pregistry);

      }

      return m_pregistry;

   }


   ::subsystem::Shell * subsystem::shell()
   {

      if (!m_pshell)
      {

         constructø(m_pshell);

      }

      return m_pshell;

   }


   ::subsystem::SystemInformationInterface *subsystem::system_information()
   {

      if (!m_psysteminformation   )
      {


         constructø(m_psysteminformation);

      }

      return m_psysteminformation;

   }


   ::subsystem::DesktopSelectorInterface *subsystem::desktop_selector()
   {

      if (!m_pdesktopselector   )
      {


         constructø(m_pdesktopselector);

      }

      return m_pdesktopselector;

   }


   ::subsystem::PipeClientInterface *subsystem::pipe_client()
   {

      if (!m_ppipeclient   )
      {


         constructø(m_ppipeclient);

      }

      return m_ppipeclient;

   }

   void subsystem::initializeCommandLineArguments(CommandLineArguments* pcommandlinearguments)
   {

      throw ::interface_only();

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


}//namespace subsystem
