// Created by camilo on 2021-01-21 14:57 <3ThomasBorregaardSorensen
// Help from http://www.winprog.org/tutorial/simple_window.html
// implementing windows::message_box 2023-12-19 04:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/operating_system/message_box.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows/windows.h"




//
//namespace windows
//{
//
//
//   class message_box:
//   public ::operating_system::message_box
//   {
//   public:
//
//      //::atom do_modal(const ::scoped_string & scopedstrMessage,
//      //                               const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox,
//      //                               const ::scoped_string & scopedstrDetails) override
//      ::enum_dialog_result m_edialogresult;
//      void run() override
//      {
//         auto iType = message_box_to_windows_message_box(m_emessagebox);
//         ::wstring wstrMessage(m_strMessage);
//         ::wstring wstrTitle(m_strTitle);
//
//         auto iRet = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, iType);
//
//         m_edialogresult = windows_message_box_result_to_dialog_result(iRet);
//
//
//      }
//
//
//      void complete_step(sequencer & sequencer) override
//      {
//
//         sequencer.add_result(m_edialogresult);
//
//      }
//
//   };
//
//
//} // namespace windows

//
//void windows_message_box_factory(::factory::factory * pfactory)
//{
//
//   pfactory->add_factory_item<::windows::message_box, ::operating_system::message_box >();
//
//}
//







namespace operating_system
{

   CLASS_DECL_ACME void message_beep(::user::enum_message_box emessagebox)
   {

      auto nType = ::windows::message_box_to_windows_message_box(emessagebox);

      ::MessageBeep(nType);

   }

} // namespace operating_system
