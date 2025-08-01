//
// Created by camilo on 2023-12-19 04:12 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#include "framework.h"
#include "message_box.h"


namespace motif
{


   ::atom message_box::do_modal(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
   //void message_box::do_modal(const_char_pointer  pszMsg, bool bError)
   {
      XmString xmString = XmStringCreateLocalized(const_cast<char *>(scopedstrMessage.c_str()));
      Arg args[6];

// setup message box text
      XtSetArg (args[0], XmNmessageString, xmString);
      XtSetArg (args[1], XmNdefaultPosition, False);
      //XtSetArg (args[2], XmNwidth
// create and label message box

      switch(emessagebox & e_message_box_icon_mask)
      {
      case e_message_box_icon_error:
         m_pwidgetMsgBox = XmCreateErrorDialog(m_pwidgetTop, (char *) "Error", args, 2);
         break;
      case e_message_box_icon_warning:
         m_pwidgetMsgBox = XmCreateWarningDialog(m_pwidgetTop, (char *) "Warning", args, 2);
         break;
      default:
         m_pwidgetMsgBox = XmCreateMessageDialog(m_pwidgetTop, (char *) "Message", args, 2);
         break;
      }
// remove text resource
      XmStringFree(xmString);
// remove help and cancel buttons
      XtUnmanageChild(XmMessageBoxGetChild(m_pwidgetMsgBox, XmDIALOG_CANCEL_BUTTON));
      XtUnmanageChild(XmMessageBoxGetChild(m_pwidgetMsgBox, XmDIALOG_HELP_BUTTON));
      XtAddCallback(m_pwidgetMsgBox, XmNmapCallback, (XtCallbackProc) s_map_dialog, this);
      XtAddCallback(m_pwidgetMsgBox, XmNokCallback, (XtCallbackProc) s_xm_close_msg_box, this);


      XtRealizeWidget(m_pwidgetTop);
// display message box
      XtManageChild(m_pwidgetMsgBox);
      XtPopup(XtParent(m_pwidgetMsgBox), XtGrabNone);
      app_main_loop();
      XtUnmanageChild(m_pwidgetMsgBox);
      XtUnrealizeWidget(m_pwidgetTop);

      return m_edialogresult;

   }


/* callback function for XmNmapCallback.  Position dialog in 200 pixel
    * "steps".  When the edge of the screen is hit, start over.
    */
   void message_box::s_map_dialog(Widget dialog, XtPointer client_data, XtPointer call_data)
   {
      
      Position x, y;
      Dimension w, h;

      XtVaGetValues(dialog,
                    XmNwidth, &w,
                    XmNheight, &h,
                    NULL);

      if (w < 600)
         w = 600;
      if (h < 200)
         h = 200;

      Dimension wScreen = WidthOfScreen (XtScreen(dialog));
      Dimension hScreen = HeightOfScreen (XtScreen(dialog));

      x = (wScreen - w) / 2;

      y = (hScreen - h) / 2;

      XtVaSetValues(dialog,
                    XmNwidth, w,
                    XmNheight, h,
                    XmNx, x,
                    XmNy, y,
                    NULL);

   }


   void message_box::s_xm_close_msg_box(Widget w, XtPointer clientData, XmPushButtonCallbackStruct * cbs)
   {

      auto p = (message_box *) clientData;
      p->set_exit_flag();
      p->m_edialogresult = e_dialog_result_ok;
   }


} // motif


void motif_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::motif::message_box, ::operating_system::message_box >();

}



