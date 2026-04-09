//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "StringParser.h"
#include "string_table.h"
#include "resource_loader.h"
#include "platform/registry.h"
#include "node/Shell.h"
#include "Registry.h"
#include "acme/exception/interface_only.h"

namespace subsystem
{


   subsystem::subsystem()
   {



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


   ::subsystem::string_table * subsystem::string_table()
   {

      if (!m_pstringtable)
      {

         constructø(m_pstringtable);

      }

      return m_pstringtable;

   }



   ::subsystem::resource_loader * subsystem::resource_loader()
   {

      if (!m_presourceloader)
      {

         constructø(m_presourceloader);

      }

      return m_presourceloader;

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



}//namespace subsystem
