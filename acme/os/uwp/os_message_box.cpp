#include "framework.h"
#include <collection.h>


bool g_bCoreWindowOnceVisible;


CLASS_DECL_ACME void set_core_window_once_visible()
{

   g_bCoreWindowOnceVisible = true;

}

bool is_core_window_once_visible()
{

   return g_bCoreWindowOnceVisible;

}

#undef new


using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;



ref class message_box_w
{
private:
   ~message_box_w()
   {

      output_debug_string("~message_box_w");

   }

internal:

   int m_iMessageBox;
   ::future     m_future;
   Platform::Agile<Windows::UI::Popups::MessageDialog> m_msg;

   message_box_w();


   ::estatus init(String ^ text, String ^ caption, ::emessagebox emessagebox, ::future future);


   void CommandInvokedHandler(IUICommand^ cmd);

};


comparable_array < message_box_w^ > g_messageboxa;




message_box_w::message_box_w()
{

}


#define create_a_button(id,text) \
   msg->Commands->Append(ref new UICommand(text,ref new UICommandInvokedHandler(this, &::message_box_w::CommandInvokedHandler),id));


::estatus message_box_w::init(String ^ text,String ^ caption, ::emessagebox emessagebox, ::future future)
{

   if (!is_core_window_once_visible())
   {

      debug_break();

      return error_failed;

   }

   MessageDialog ^ msg = ref new MessageDialog(text, caption);

   m_msg = msg;

   u32 uiType = emessagebox & MB_TYPEMASK;

   int iCancel = -1;

   switch (uiType)
   {
   case MB_OKCANCEL:
      create_a_button("ok", "OK");
      create_a_button("cancel", "Cancel");
      iCancel = 1;
   break;
   case MB_ABORTRETRYIGNORE:
      create_a_button("abort", "Abort");
      create_a_button("retry", "Retry");
      create_a_button("ignore", "Ignore");
   break;
   case MB_YESNOCANCEL:
      create_a_button("yes", "Yes");
      create_a_button("no", "No");
      create_a_button("cancel", "Cancel");
      iCancel = 2;
   break;
   case MB_YESNO:
      create_a_button("yes", "Yes");
      create_a_button("no", "No");
   break;
   case MB_RETRYCANCEL:
      create_a_button("retry", "Retry");
      create_a_button("cancel", "Cancel");
      iCancel = 1;
   break;
   case MB_CANCELTRYCONTINUE:
      create_a_button("cancel", "Cancel");
      create_a_button("try", "Try");
      create_a_button("continue", "Continue");
      iCancel = 0;
   break;
   default:
      create_a_button("ok", "OK");
   break;
   }

   msg->DefaultCommandIndex = 0;

   if (iCancel >= 0)
   {

      msg->CancelCommandIndex = iCancel;

   }

   m_future = future;


   return ::success;

}

::estatus _os_message_box(const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::future future)
{

   message_box_w ^ pmessageboxw = ref new message_box_w;

   pmessageboxw->init(wstring(pszMessage),wstring(pszTitle), emessagebox, future);

   g_messageboxa.add(pmessageboxw);

   main_async([pmessageboxw]()
      {

         pmessageboxw->m_msg->ShowAsync();

      });

   return ::success;

}



void message_box_w::CommandInvokedHandler(IUICommand^ cmd)
{

   if (cmd == nullptr)
   {

      m_future.send(::error_failed);

   }
   else
   {

      wstring wstr(cmd->Id);

      string str(wstr);

      m_future.send(str);

   }

   // Display message showing the label of the command that was invoked
   //rootPage.NotifyUser("The '" + command.Label + "' command has been selected.",
      //NotifyType.StatusMessage);
   g_messageboxa.remove(this);

}





