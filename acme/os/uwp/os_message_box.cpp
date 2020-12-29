#include "framework.h"
#include <collection.h>


//void keep_sealed_object(Object ^ o);
//void remove_sealed_object(Object ^ o);
//
//
//template < typename T, typename PRED >
//ref class chain_for_Windows_Foundation_IAsyncOperation sealed
//{
//private:
//
//
//   ::Windows::Foundation::IAsyncOperation < T > ^     m_operation;
//   ::Windows::Foundation::AsyncStatus                 m_status;
//   T                                                  m_result;
//   HRESULT                                            m_hresult;
//   PRED                                               m_pred;
//
//
//private:
//
//   
//   template < typename T, typename PRED >
//   friend void chain(::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, CallbackContext callbackcontext);
//
//
//   chain_for_Windows_Foundation_IAsyncOperation(::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, CallbackContext callbackcontext = CallbackContext::Any) :
//      m_pred(pred)
//   {
//
//      m_operation = operation;
//
//      m_operation->Completed = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < T >([this](::Windows::Foundation::IAsyncOperation < T > ^ operation, ::Windows::Foundation::AsyncStatus status)
//      {
//
//         m_status = status;
//
//         if (m_status == ::Windows::Foundation::AsyncStatus::Completed)
//         {
//
//               m_pred(m_operation->GetResults());
//
//         }
//         else
//         {
//
//            m_pred(nullptr);
//
//         }
//
//      });
//
//   }
//
//
//public:
//
//
//   virtual ~chain_for_Windows_Foundation_IAsyncOperation()
//   {
//
//   }
//
//
//internal:
//
//
//};


//mutex g_mutexSealed;


//set < Object ^ >  g_setSealed;
//
//
//void keep_sealed_object(Object ^ o)
//{
//
//   sync_lock sl(&g_mutexSealed);
//
//   g_setSealed.add(o);
//
//}
//
//
//void remove_sealed_object(Object ^ o)
//{
//
//   sync_lock sl(&g_mutexSealed);
//
//   g_setSealed.remove(o);
//
//}


template < typename T, typename PRED >
void chain(::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, CallbackContext callbackcontext = CallbackContext::Any)
{

   operation->Completed = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < T >([pred](::Windows::Foundation::IAsyncOperation < T > ^ operation, ::Windows::Foundation::AsyncStatus status)
   {

      if (status == ::Windows::Foundation::AsyncStatus::Completed)
      {

         pred(operation->GetResults());

      }
      else
      {

         pred(nullptr);

      }

   }, callbackcontext);

}


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

   int                     m_iMessageBox;
   ::promise::process      m_process;

   message_box_w();


   ::e_status show(String ^ text, String ^ caption, const ::e_message_box & emessagebox, const ::promise::process & process);


   void CommandInvokedHandler(IUICommand^ cmd);

};


comparable_array < message_box_w ^ > g_messageboxa;


message_box_w::message_box_w()
{

}


#define create_a_button(id,text) \
   msg->Commands->Append(ref new UICommand(text,ref new UICommandInvokedHandler(this, &::message_box_w::CommandInvokedHandler),id));


::e_status message_box_w::show(String ^ text,String ^ caption, const ::e_message_box & emessagebox, const ::promise::process & process)
{

   if (!is_core_window_once_visible())
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

   m_process = process;

   chain(msg->ShowAsync(), [this](IUICommand ^ i)
   {

      CommandInvokedHandler(i);

   });

   return ::success;

}


::e_status _os_message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process)
{

   wstring wstrMessage(pszMessage);

   wstring wstrTitle(pszTitle);

   auto psystem = ::get_context_system();

   message_box_w ^ pmessageboxw = ref new message_box_w;

   pmessageboxw->show(wstrMessage, wstrTitle, emessagebox, process);

   return ::success;

}


void message_box_w::CommandInvokedHandler(IUICommand^ cmd)
{

   if (cmd == nullptr)
   {

      m_process(::error_failed);

   }
   else
   {

      wstring wstr(cmd->Id);

      string str(wstr);

      m_process(str);

   }

}



