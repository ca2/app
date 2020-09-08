#pragma once


template < typename T >
inline void waiter_null_result(T & t)
{
   t = nullptr;
}

template < >
inline void waiter_null_result(bool & b)
{
   b = false;
}

template < >
inline void waiter_null_result(unsigned int & ui)
{
   ui = NULL;
}


template < typename T >
ref class waiter_for_Windows_Foundation_IAsyncOperation sealed
{
private:

   manual_reset_event                                 m_event;
   ::Windows::Foundation::IAsyncOperation < T > ^     m_operation;
   ::Windows::Foundation::AsyncStatus                 m_status;
   T                                                  m_result;
   HRESULT                                            m_hresult;


public:


   waiter_for_Windows_Foundation_IAsyncOperation(::Windows::Foundation::IAsyncOperation < T > ^ operation, CallbackContext callbackcontext = CallbackContext::Any)
   {

      m_operation             = operation;

      m_operation->Completed  = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < T > ([this](::Windows::Foundation::IAsyncOperation < T > ^ operation, ::Windows::Foundation::AsyncStatus status)
      {

         m_status = status;

         m_event.set_event();

      });

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperation()
   {

   }


   T wait(unsigned int dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      thread_sleep(millis(dwMillis), &m_event);

      if (pstatus != nullptr)
      {

         *pstatus = m_status;

      }

      m_hresult = m_operation->ErrorCode.Value;

      if(m_status == ::Windows::Foundation::AsyncStatus::Completed)
      {

         return m_operation->GetResults();

      }
      else
      {

         T t;

         waiter_null_result(t);

         return t;

      }

   }

internal:

   template < typename PRED >
   void wait(PRED pred,unsigned int dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      pred(wait(dwMillis, pstatus));

   }


};


template < typename T, typename T2 >
ref class waiter_for_Windows_Foundation_IAsyncOperationWithProgress sealed
{
private:

   manual_reset_event                                                m_event;
   ::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^    m_operation;
   ::Windows::Foundation::AsyncStatus                                m_status;
   T                                                                 m_result;


public:


   waiter_for_Windows_Foundation_IAsyncOperationWithProgress(::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, CallbackContext callbackcontext = CallbackContext::Any)
   {

      m_operation = operation;

      m_operation->Completed = ref new ::Windows::Foundation::AsyncOperationWithProgressCompletedHandler < T, T2 >([this](::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, ::Windows::Foundation::AsyncStatus status)
      {

         auto pholdThis = this;

         m_status = status;

         m_event.set_event();

      });

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperationWithProgress()
   {

   }


   T wait(unsigned int dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      m_event.wait(millis(dwMillis));

      if (pstatus != nullptr)
         *pstatus = m_status;

      if (m_status == ::Windows::Foundation::AsyncStatus::Completed)
      {

         return m_operation->GetResults();

      }
      else
      {

         T t;

         waiter_null_result(t);

         return t;

      }

   }

};


ref class waiter_for_Windows_Foundation_IAsyncAction sealed
{
private:


   manual_reset_event                                 m_event;
   ::Windows::Foundation::IAsyncAction ^              m_action;
   ::Windows::Foundation::AsyncStatus                 m_status;

public:


   waiter_for_Windows_Foundation_IAsyncAction(::Windows::Foundation::IAsyncAction ^ action, CallbackContext callbackcontext = CallbackContext::Any)
   {

      m_action                = action;

      m_action->Completed     = ref new ::Windows::Foundation::AsyncActionCompletedHandler([this](::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
      {

         auto pholdThis = this;

         m_status = status;

         m_event.set_event();

      });

      if(m_action->Status != ::Windows::Foundation::AsyncStatus::Started)
      {

         m_status = m_action->Status;

         m_event.set_event();

      }

   }

   virtual ~waiter_for_Windows_Foundation_IAsyncAction()
   {

   }


   void wait(unsigned int dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      auto pholdThis = this;

      m_event.wait(millis(dwMillis));

      if(pstatus != nullptr)
         *pstatus = m_status;

   }


};


template < typename T, typename PRED >
void fork_then(::generic * pobject, ::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, DWORD dwMillis = INFINITE, CallbackContext callbackcontext = CallbackContext::Any)
{

   pobject->fork([=]()
   {

      auto pwaiter = ref new waiter_for_Windows_Foundation_IAsyncOperation < T >(operation, callbackcontext);

      pwaiter->wait(pred, dwMillis);

   });

}


template < typename T, typename PRED >
inline void wait_then(::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, DWORD dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = nullptr, CallbackContext callbackcontext = CallbackContext::Any)
{

   auto pwaiter = ref new waiter_for_Windows_Foundation_IAsyncOperation < T >(operation, callbackcontext);

   pwaiter->wait(pred, dwMillis, pstatus);

}


template < typename T >
inline T wait(::Windows::Foundation::IAsyncOperation < T > ^ operation, DWORD dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = nullptr, CallbackContext callbackcontext = CallbackContext::Any)
{

   auto pwaiter = ref new waiter_for_Windows_Foundation_IAsyncOperation < T >(operation, callbackcontext);

   return pwaiter->wait(dwMillis, pstatus);

}


template < typename T, typename T2 >
inline T wait(::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, DWORD dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = nullptr, CallbackContext callbackcontext = CallbackContext::Any)
{

   auto pwaiter = ref new waiter_for_Windows_Foundation_IAsyncOperationWithProgress < T, T2 > (operation, callbackcontext);

   return pwaiter->wait(dwMillis, pstatus);

}


inline ::Windows::Foundation::AsyncStatus wait(::Windows::Foundation::IAsyncAction ^ action,  DWORD dwMillis = INFINITE, CallbackContext callbackcontext = CallbackContext::Any)
{

   ::Windows::Foundation::AsyncStatus status = ::Windows::Foundation::AsyncStatus::Canceled; // for time out

   auto pwaiter = ref new waiter_for_Windows_Foundation_IAsyncAction (action, callbackcontext);

   pwaiter->wait(dwMillis, &status);

   return status;

}



