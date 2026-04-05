//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "string_table.h"
#include "resource_loader.h"
#include "platform/registry.h"
#include "node/Shell.h"
#include "Registry.h"


namespace subsystem
{


   subsystem::subsystem()
   {



   }


   subsystem::~subsystem()
   {


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



}//namespace subsystem
