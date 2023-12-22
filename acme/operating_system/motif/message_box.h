//
// Created by camilo on 2023-12-19 04:12 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#pragma once


#include "acme/operating_system/message_box.h"
#include "application.h"
#define register
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/MessageB.h>
#include <X11/Intrinsic.h>
#undef register


namespace motif
{


   class message_box :
      virtual public ::operating_system::message_box,
      virtual public ::motif::application
   {
   public:


      Widget                     m_pwidgetMsgBox;
      enum_dialog_result         m_edialogresult;


      ::atom do_modal(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails) override;
      //void do_modal(const char * pszMsg, bool bError) override;


      static void s_map_dialog(Widget dialog, XtPointer client_data, XtPointer call_data);

      static void s_xm_close_msg_box(Widget w, XtPointer clientData, XmPushButtonCallbackStruct * cbs);


   };


} // namespace motif


//
////#include <iostream>
////
//int main(int argc, char ** argv)
//{
//   g_argc = argc;
//   g_argv = argv;
//
//   xt_message_box messagebox;
//
//   messagebox.do_modal("People", false);
//
//   return 0;
//
//}
//
//
