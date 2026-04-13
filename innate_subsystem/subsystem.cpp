//
// Created by camilo on 2026-04-06 10:54 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "gui/SystemMetrics.h"
#include "resource_loader.h"
#include "acme/constant/user_key.h"
#include "gui/Window.h"


namespace innate_subsystem
{

   ::innate_subsystem::subsystem * subsystem::s_p = nullptr;

   subsystem::subsystem()
   {

s_p = this;

   }


   subsystem::~subsystem()
   {


   }


   // ::innate_subsystem::resource_loader * subsystem::resource_loader()
   // {
   //
   //    if (!m_presourceloader)
   //    {
   //
   //       m_presourceloader = ::subsystem::subsystem::resource_loader();
   //
   //    }
   //
   //    return m_presourceloader;
   //
   // }
   //

   //
   // ::subsystem::string_table * subsystem::string_table()
   // {
   //
   //    if (!m_pstringtable)
   //    {
   //
   //       constructø(m_pstringtable);
   //
   //    }
   //
   //    return m_pstringtable;
   //
   // }
   //
   //
   //
   ::innate_subsystem::resource_loader * subsystem::resource_loader()
   {


      if (!m_presourceloader)
      {
         m_presourceloader = ::subsystem::subsystem::resource_loader();
      }

      return m_presourceloader;

   }




   int subsystem::message_box(
      const ::user_interaction_sink & userinteractionsink,
      const ::scoped_string & scopedstrMessage,
      const ::scoped_string & scopedstrCaption,
      unsigned int uType)
   {

      throw ::interface_only();

      return ::innate_subsystem::e_control_id_cancel;

   }

   //
   //
   // ::subsystem::Registry * subsystem::registry()
   // {
   //
   //    if (!m_pregistry)
   //    {
   //
   //       construct_newø(m_pregistry);
   //
   //    }
   //
   //    return m_pregistry;
   //
   // }
   //
   //
   // ::subsystem::Shell * subsystem::shell()
   // {
   //
   //    if (!m_pshell)
   //    {
   //
   //       constructø(m_pshell);
   //
   //    }
   //
   //    return m_pshell;
   //
   // }
   //
   // ::pointer < ::subsystem::SecurityIdentifier > subsystem::createSidFromString(const ::scoped_string & scopedstr)
   // {
   //
   //    return nullptr;
   //
   // }

   ::innate_subsystem::SystemMetricsInterface * subsystem::metrics()
   {

      if (!m_psystemmetrics)
      {

         constructø(m_psystemmetrics);

      }

      return m_psystemmetrics;

   }

   ::user::enum_key subsystem::virtual_key_code_to_user_key(int iVirtualKeyCode)
   {

      throw ::interface_only();

      return ::user::e_key_none;

   }


   ::pointer < ::innate_subsystem::WindowInterface > subsystem::getWindow(const ::operating_system::window & window)
   {

      return m_mapWindow[window];

   }

   void subsystem::setWindow(const ::operating_system::window & window, ::innate_subsystem::WindowInterface * pwindow)
   {

      m_mapWindow[window] = pwindow;

   }

}//namespace innate_subsystem
