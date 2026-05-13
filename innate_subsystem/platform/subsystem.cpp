//
// Created by camilo on 2026-04-06 10:54 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "gui/SystemMetrics.h"
#include "ResourceLoader.h"
#include "acme/constant/user_key.h"
#include "gui/Window.h"
#include "gui/KeyboardLayout.h"
#include "drawing/SolidBrush.h"


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
   ::innate_subsystem::ResourceLoader *subsystem::ResourceLoader()
   {


      if (!m_presourceloader)
      {
         m_presourceloader = ::subsystem::subsystem::ResourceLoader();
      }

      return m_presourceloader;

   }

   
    ::innate_subsystem::KeyboardLayoutInterface *subsystem::keyboard_layout()
   {

      if (!m_pkeyboardlayout)
      {

         constructø(m_pkeyboardlayout);
      }

      return m_pkeyboardlayout;
   }
::string subsystem::getKeyboardLayoutName()
{
   
   throw ::interface_only();
#ifdef WINDOWS
   wstring kbdName;
   auto pwsz= kbdName.get_buffer(KL_NAMELENGTH);
   //memset(&kbdName[0], 0, sizeof(TCHAR) * KL_NAMELENGTH);
   if (!GetKeyboardLayoutNameW( pwsz ))
   {
      pwsz[0] = '?';
      pwsz[1] = '?';
      pwsz[2] = '?';
   }
   kbdName.release_buffer();
#endif
   
   return "";
   
}


   ::enum_dialog_result subsystem::message_box(
      const ::user_interaction_sink & userinteractionsink,
      const ::scoped_string & scopedstrMessage,
      const ::scoped_string & scopedstrCaption,
      ::user::enum_message_box emessagebox)
   {

      throw ::interface_only();

      return ::e_dialog_result_ok;

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

   void subsystem::initializeInnateSubsystemControls()
   {


   }

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


::pointer < ::innate_subsystem::SolidBrushInterface > subsystem::createSolidBrush(const ::color::color & color)
{
   
   auto pbrush = createø<::innate_subsystem::SolidBrushInterface>();
   
   pbrush->initialize_solid_brush(color);
   
   return pbrush;
   
}
   
   void subsystem::releaseMouseCapture()
   {
      
      
   }
   ::operating_system::window subsystem::getMouseCapture()
   {
      
      return {};
      
   }
   void subsystem::setMouseCapture(const ::operating_system::window & operatingsystemwindow)
   {
      
      
   }
   
   
    ::user::key_happening subsystem::keyHappeningFromKeyMessage(::wparam wparam, ::lparam lparam)
   {
      
#ifdef WINDOWS
      
      unsigned short virtualKey = static_cast<unsigned short>(wParam);
      ::u32 additionalInfo = static_cast<::u32>(lParam);
      static const ::u32 DOWN_FLAG = 0x80000000;
      bool isDown = (additionalInfo & DOWN_FLAG) == 0;

      if (virtualKey == VK_PROCESSKEY)
      {
          bool extended = HIWORD(lParam) & KF_EXTENDED;
          ::u32 scancode = HIWORD(lParam) & 0xFF;
          if (extended)
          {
              scancode += 0xE000;
          }
          virtualKey = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
      }

      if (virtualKey == VK_CONTROL)
      {
          m_ctrlDown = isDown;
      }

      if (virtualKey == VK_MENU)
      {
          m_altDown = isDown;
      }

      //m_rfbKeySym->processKeyEvent(virtualKey, additionalInfo);
      m_rfbKeySym->processKeyEvent(keyhappening?!?!);
#endif
      
       return {};
       
   }


}//namespace innate_subsystem
