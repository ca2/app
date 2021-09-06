#include "framework.h"
#include "acme/operating_system.h"


//#include <collection.h>


//void keep_sealed_object(Object ^ o);
//void erase_sealed_object(Object ^ o);
//
//
//template < typename T, typename PRED >
//ref class chain_for_Windows_Foundation_IAsyncOperation sealed
//{
//private:
//
//
//   ::winrt::Windows::Foundation::IAsyncOperation < T > ^     m_operation;
//   ::winrt::Windows::Foundation::AsyncStatus                 m_status;
//   T                                                  m_result;
//   HRESULT                                            m_hresult;
//   PRED                                               m_predicate;
//
//
//private:
//
//   
//   template < typename T, typename PRED >
//   friend void chain(::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, CallbackContext callbackcontext);
//
//
//   chain_for_Windows_Foundation_IAsyncOperation(::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, CallbackContext callbackcontext = CallbackContext::Any) :
//      m_predicate(pred)
//   {
//
//      m_operation = operation;
//
//      m_operation->Completed = ref new ::winrt::Windows::Foundation::AsyncOperationCompletedHandler < T >([this](::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, ::winrt::Windows::Foundation::AsyncStatus status)
//      {
//
//         m_status = status;
//
//         if (m_status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
//         {
//
//               m_predicate(m_operation->GetResults());
//
//         }
//         else
//         {
//
//            m_predicate(nullptr);
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


//::mutex g_mutexSealed;


//set < Object ^ >  g_setSealed;
//
//
//void keep_sealed_object(Object ^ o)
//{
//
//   synchronous_lock synchronouslock(&g_mutexSealed);
//
//   g_setSealed.add(o);
//
//}
//
//
//void erase_sealed_object(Object ^ o)
//{
//
//   synchronous_lock synchronouslock(&g_mutexSealed);
//
//   g_setSealed.erase(o);
//
//}


//template < typename T, typename PRED >
//void chain(::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, CallbackContext callbackcontext = CallbackContext::Any)
//{
//
//   operation->Completed = ref new ::winrt::Windows::Foundation::AsyncOperationCompletedHandler < T >([pred](::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, ::winrt::Windows::Foundation::AsyncStatus status)
//   {
//
//      if (status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
//      {
//
//         pred(operation->GetResults());
//
//      }
//      else
//      {
//
//         auto ErrorCode = operation->ErrorCode;
//
//         pred(nullptr);
//
//      }
//
//   }, callbackcontext);
//
//}


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


//using namespace ::winrt::Windows::UI::Popups;
//using namespace ::winrt::Windows::UI::Xaml;
//using namespace ::winrt::Windows::UI::Xaml::Controls;
//using namespace ::winrt::Windows::UI::Xaml::Navigation;


class message_box_w;

ref class message_box_callback
{
private:


   ::message_box_w * m_pmessageboxw;
   Platform::Agile<::winrt::Windows::UI::Popups::MessageDialog> m_messagedialog;

   ~message_box_callback()
   {
      output_debug_string("~message_box_w");

   }

internal:

   
   int                     m_iMessageBox;
   ::future      m_process;


   message_box_callback(::message_box_w * pmessageboxw);


   ::e_status show(String ^ text, String ^ caption, const ::e_message_box & emessagebox, const ::future & process);


   void CommandInvokedHandler(IUICommand^ cmd);

};


class message_box_w :
   virtual public ::matter
{
public:

   message_box_callback ^ m_pcallback;

   message_box_w();
   virtual ~message_box_w();


   ::e_status show(const ::string & strText, const ::string & strCaption, const ::e_message_box & emessagebox, const ::future & process);


};


//comparable_array < message_box_callback ^ > g_messageboxa;


message_box_callback::message_box_callback(::message_box_w * pmessageboxw)
{

   m_pmessageboxw = pmessageboxw;

}


#define create_a_button(id,text) \
   messagedialog->Commands->Append(ref new UICommand(text,ref new UICommandInvokedHandler(this, &::message_box_callback::CommandInvokedHandler),id));


::e_status message_box_callback::show(String ^ text,String ^ caption, const ::e_message_box & emessagebox, const ::future & process)
{

   if (!is_core_window_once_visible())
   {

      debug_break();

      return error_failed;

   }

   MessageDialog ^ messagedialog = ref new MessageDialog(text, caption);

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

   messagedialog->DefaultCommandIndex = 0;

   if (iCancel >= 0)
   {

      messagedialog->CancelCommandIndex = iCancel;

   }

   m_process = process;

   m_messagedialog = messagedialog;

   auto phandler = [this]()
   {

      m_messagedialog->ShowAsync();

   };

   auto pdispatchedhandler = ref new ::winrt::Windows::UI::Core::DispatchedHandler(phandler);

   auto pdispatcher = ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher;

   pdispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, pdispatchedhandler);

   return ::success;

}


//message_box_w();
//virtual ~message_box_w();


::e_status message_box_w::show(const ::string & strText, const ::string & strCaption, const ::e_message_box & emessagebox, const ::future & process)
{

   wstring wstrMessage(strText);

   wstring wstrTitle(strCaption);

   m_pcallback = ref new message_box_callback(this);

   auto estatus = m_pcallback->show(wstrMessage, wstrTitle, emessagebox, process);

   return estatus;

}


::e_status _os_message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, const ::future & process)
{

   auto pmessagebox = __new(message_box_w);

   auto psystem = ::get_context_system();

   auto pobjectarray = psystem->payload("message_box_array").cast < ::object_array >();
   
   if (!pobjectarray)
   {

      psystem->payload("message_box_array") = __new(object_array);

      pobjectarray = psystem->payload("message_box_array").cast < ::object_array >();

   }

   pobjectarray->add_item(pmessagebox);

   pmessagebox->show(pszMessage, pszTitle, emessagebox, process);
   
   return ::success;

}


void message_box_callback::CommandInvokedHandler(IUICommand^ cmd)
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

   auto psystem = ::get_context_system();

   auto pobjectarray = psystem->payload("message_box_array").cast < ::object_array >();

   pobjectarray->erase(m_pmessageboxw);


}







message_box_w::message_box_w()
{

}



message_box_w::~message_box_w()
{


}
