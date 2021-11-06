#include "framework.h"


extern bool g_bCoreWindowOnceVisible;

#undef new


using namespace ::winrt::Windows::UI::Popups;
using namespace ::winrt::Windows::UI::Xaml;
using namespace ::winrt::Windows::UI::Xaml::Controls;
using namespace ::winrt::Windows::UI::Xaml::Navigation;


ref class message_box_w
{
internal:


   ::future     m_future;


   message_box_w();


   ::e_status show(String ^ text, String ^ caption, const ::e_message_box & emessagebox, ::callback callback);


   void CommandInvokedHandler(IUICommand^ cmd)
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

   }


};


message_box_w::message_box_w()
{

}


#define create_a_button(id,text) \
   msg->Commands->Append(ref new UICommand(text,ref new UICommandInvokedHandler(this, &::message_box_w::CommandInvokedHandler),id));


::e_status message_box_w::show(String ^ text,String ^ caption, const ::e_message_box & emessagebox, ::future future)
{

   if (!g_bCoreWindowOnceVisible)
   {

      debug_break();

      return error_failed;

   }

   MessageDialog ^ msg = ref new MessageDialog(text, caption);

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

   msg->ShowAsync();

   return ::success;

}


::e_status os_message_box(oswindow oswindow, const char * pszText, const char * pszCaption, emessagebox emessagebox, ::callback callback)
{

   __UNREFERENCED_PARAMETER(oswindow);

   message_box_w a;

   int iResult = a.show(wstring(pszText),wstring(pszCaption), emessagebox, callback);

   return iResult;

}



