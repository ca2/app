#include "framework.h"
#include <collection.h>

template < typename T >
ref class promisse_for_Windows_Foundation_IAsyncOperation sealed
{
private:

   //manual_reset_event                                 m_event;
   ::Windows::Foundation::IAsyncOperation < T > ^ m_operation;
   ::Windows::Foundation::AsyncStatus                 m_status;
   T                                                  m_result;
   HRESULT                                            m_hresult;


public:


   waiter_for_Windows_Foundation_IAsyncOperation(::Windows::Foundation::IAsyncOperation < T > ^ operation, CallbackContext callbackcontext = CallbackContext::Any)
   {

      m_operation = operation;

      m_operation->Completed = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < T >([this](::Windows::Foundation::IAsyncOperation < T > ^ operation, ::Windows::Foundation::AsyncStatus status)
         {

            m_status = status;

            if (m_status == ::Windows::Foundation::AsyncStatus::Completed)
            {

                m_operation->GetResults();

            }
            else
            {

               T t;

               waiter_null_result(t);

               return t;

            }


         });

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperation()
   {

   }

   template < typename PRED >
   void then(PRED pred)
   {

      m_future = __future(pred);

   }


   //T wait(unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   //{

   //   task_sleep(dwMillis, &m_event);

   //   if (pstatus != nullptr)
   //   {

   //      *pstatus = m_status;

   //   }

   //   m_hresult = m_operation->ErrorCode.Value;

   //   if (m_status == ::Windows::Foundation::AsyncStatus::Completed)
   //   {

   //      return m_operation->GetResults();

   //   }
   //   else
   //   {

   //      T t;

   //      waiter_null_result(t);

   //      return t;

   //   }

   //}

internal:

   template < typename PRED >
   void wait(PRED pred, unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      pred(wait(dwMillis, pstatus));

   }


};



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

   message_box_w();


   ::estatus init(String ^ text, String ^ caption, ::emessagebox emessagebox, const ::future & future);


   void CommandInvokedHandler(IUICommand^ cmd);

};


comparable_array < message_box_w^ > g_messageboxa;




message_box_w::message_box_w()
{

}


#define create_a_button(id,text) \
   msg->Commands->Append(ref new UICommand(text,ref new UICommandInvokedHandler(this, &::message_box_w::CommandInvokedHandler),id));


::estatus message_box_w::init(String ^ text,String ^ caption, ::emessagebox emessagebox, const ::future & future)
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

::estatus _os_message_box(const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, const ::future & future)
{

   wstring wstrMessage(pszMessage);

   wstring wstrTitle(pszTitle);

   //g_messageboxa.add(pmessageboxw);

   auto psystem = ::get_context_system();

   //psystem->main_user_async(__procedure([wstrMessage, wstrTitle, emessagebox, future]()
     // {

         message_box_w ^ pmessageboxw = ref new message_box_w;

         pmessageboxw->init(wstrMessage, wstrTitle, emessagebox, future);

       //  g_messageboxa.add_item(pmessageboxw);

         wait(pmessageboxw->m_msg->ShowAsync())->
            then([pmessageboxw](IUICommand ^ i)
               {

                  pmessageboxw->CommandInvokedHandler(i);

               });

      //}));

   return ::success;

}



void message_box_w::CommandInvokedHandler(IUICommand^ cmd)
{

   if (cmd == nullptr)
   {

      m_future(::error_failed);

   }
   else
   {

      wstring wstr(cmd->Id);

      string str(wstr);

      m_future(str);

   }

   // Display message showing the label of the command that was invoked
   //rootPage.NotifyUser("The '" + command.Label + "' command has been selected.",
      //NotifyType.StatusMessage);
   //g_messageboxa.remove(this);

}





