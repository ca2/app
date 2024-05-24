//
// Created by camilo on 2023-12-19 04:57 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#include "framework.h"
#include "message_box.h"

enum_dialog_result ns_alert_box(const char * pszMessage, const char * pszTitle, enum_message_box emessagebox);

namespace macos
{


   ::atom message_box::do_modal(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
   {

      ::string strMessage(scopedstrMessage);
      ::string strTitle(scopedstrTitle);

      auto edialogresult = ns_alert_box(strMessage, strTitle, emessagebox);

      return edialogresult;

   }

//#else
//   real_message_box_fallback();
//#endif


} // macos


void macos_message_box_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::macos::message_box, ::operating_system::message_box >();

}



