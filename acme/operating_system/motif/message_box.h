//
// Created by camilo on 12/19/23.
//

#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/MessageB.h>
#include <X11/Intrinsic.h>

int g_argc;
char** g_argv;


class xt_app {
public:

   XtAppContext m_pappcontext;
   Widget m_pwidgetTop;


   xt_app()
   {


      m_pwidgetTop = XtVaAppInitialize (&m_pappcontext, "Application Name", NULL, 0,
                                        &g_argc, g_argv, NULL, NULL);


   }

   void set_exit_flag()
   {
      XtAppSetExitFlag(m_pappcontext);

   }

   void app_main_loop()
   {

      XtAppMainLoop (m_pappcontext);
   }

};


class xt_message_box :
   public xt_app{
public:

   Widget   m_pwidgetMsgBox;
   void do_modal (const char* pszMsg, bool bError)
   {
      XmString xmString = XmStringCreateLocalized (const_cast<char*>(pszMsg));
      Arg      args [6];

// setup message box text
      XtSetArg (args [0], XmNmessageString, xmString);
      XtSetArg (args[1], XmNdefaultPosition,False);
      //XtSetArg (args[2], XmNwidth
// create and label message box
      auto xMsgBox = bError
                     ? XmCreateErrorDialog (m_pwidgetTop, (char*) "Error", args, 2)
                     : XmCreateWarningDialog (m_pwidgetTop, (char*) "Warning", args, 2);
// remove text resource
      XmStringFree (xmString);
// remove help and cancel buttons
      XtUnmanageChild (XmMessageBoxGetChild (xMsgBox, XmDIALOG_CANCEL_BUTTON));
      XtUnmanageChild (XmMessageBoxGetChild (xMsgBox, XmDIALOG_HELP_BUTTON));
      XtAddCallback (xMsgBox, XmNmapCallback, (XtCallbackProc) s_map_dialog, this);
      XtAddCallback (xMsgBox, XmNokCallback, (XtCallbackProc) s_xm_close_msg_box, this);


      XtRealizeWidget (m_pwidgetTop);
// display message box
      XtManageChild (xMsgBox);
      XtPopup (XtParent(xMsgBox), XtGrabNone);
      app_main_loop();
   }
/* callback function for XmNmapCallback.  Position dialog in 200 pixel
    * "steps".  When the edge of the screen is hit, start over.
    */
   static void s_map_dialog(Widget dialog, XtPointer client_data, XtPointer call_data)
   {
      Position x, y;
      Dimension w, h;

      XtVaGetValues(dialog,
                    XmNwidth, &w,
                    XmNheight, &h,
                    NULL);

      if(w < 600)
         w = 600;
      if(h < 200)
         h = 200;

      Dimension wScreen =WidthOfScreen (XtScreen (dialog));
      Dimension hScreen =HeightOfScreen (XtScreen (dialog));

      x = (wScreen - w)/2;

      y = (hScreen - h)/2;

      XtVaSetValues (dialog,
                     XmNwidth, w,
                     XmNheight, h,
                     XmNx, x,
                     XmNy, y,
                     NULL);

   }
   static void s_xm_close_msg_box (Widget w, XtPointer clientData, XmPushButtonCallbackStruct *cbs)
   {

      auto p = (xt_message_box *) clientData;
      p->set_exit_flag();
   }

};





//#include <iostream>
//
int main(int argc, char ** argv)
{
   g_argc = argc;
   g_argv = argv;

   xt_message_box messagebox;

   messagebox.do_modal("People", false);

   return 0;

}
