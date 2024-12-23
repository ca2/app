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
inline void waiter_null_result(unsigned int & u)
{
   u = NULL;
}


template < typename T >
ref class waiter_for_Windows_Foundation_IAsyncOperation sealed
{
private:

   manual_reset_happening                                 m_happening;
   ::winrt::Windows::Foundation::IAsyncOperation < T > ^     m_operation;
   ::winrt::Windows::Foundation::AsyncStatus                 m_status;
   T                                                  m_result;
   HRESULT                                            m_hresult;


public:


   waiter_for_Windows_Foundation_IAsyncOperation(::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, CallbackContext callbackcontext = CallbackContext::Any)
   {

      m_operation             = operation;

      m_operation->Completed  = ref aaa_primitive_new ::winrt::Windows::Foundation::AsyncOperationCompletedHandler < T > ([this](::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, ::winrt::Windows::Foundation::AsyncStatus status)
      {

         m_status = status;

         m_happening.set_happening();

      });

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperation()
   {

   }


   T wait(unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      task_sleep(::duration(dwMillis), &m_happening);

      if (pstatus != nullptr)
      {

         *pstatus = m_status;

      }

      m_hresult = m_operation->ErrorCode.Value;

      if(m_status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
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
   void wait(PRED pred,unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      pred(wait(dwMillis, pstatus));

   }


};


template < typename T, typename T2 >
ref class waiter_for_Windows_Foundation_IAsyncOperationWithProgress sealed
{
private:

   manual_reset_happening                                                m_happening;
   ::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^    m_operation;
   ::winrt::Windows::Foundation::AsyncStatus                                m_status;
   T                                                                 m_result;


public:


   waiter_for_Windows_Foundation_IAsyncOperationWithProgress(::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, CallbackContext callbackcontext = CallbackContext::Any)
   {

      m_operation = operation;

      m_operation->Completed = ref aaa_primitive_new ::winrt::Windows::Foundation::AsyncOperationWithProgressCompletedHandler < T, T2 >([this](::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, ::winrt::Windows::Foundation::AsyncStatus status)
      {

         auto pholdThis = this;

         m_status = status;

         m_happening.set_happening();

      });

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperationWithProgress()
   {

   }


   T wait(unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      m_happening.wait(::duration(dwMillis));

      if (pstatus != nullptr)
         *pstatus = m_status;

      if (m_status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
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


   manual_reset_happening                                 m_happening;
   ::winrt::Windows::Foundation::IAsyncAction ^              m_action;
   ::winrt::Windows::Foundation::AsyncStatus                 m_status;

public:


   waiter_for_Windows_Foundation_IAsyncAction(::winrt::Windows::Foundation::IAsyncAction ^ action, CallbackContext callbackcontext = CallbackContext::Any)
   {

      m_action                = action;

      m_action->Completed     = ref aaa_primitive_new ::winrt::Windows::Foundation::AsyncActionCompletedHandler([this](::winrt::Windows::Foundation::IAsyncAction ^ action, ::winrt::Windows::Foundation::AsyncStatus status)
      {

         auto pholdThis = this;

         m_status = status;

         m_happening.set_happening();

      });

      if(m_action->Status != ::winrt::Windows::Foundation::AsyncStatus::Started)
      {

         m_status = m_action->Status;

         m_happening.set_happening();

      }

   }

   virtual ~waiter_for_Windows_Foundation_IAsyncAction()
   {

   }


   void wait(unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
   {

      auto pholdThis = this;

      m_happening.wait(::duration(dwMillis));

      if(pstatus != nullptr)
         *pstatus = m_status;

   }


};


template < typename T, typename PRED >
void fork_then(::particle * pparticle, ::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, unsigned int dwMillis = U32_INFINITE_TIMEOUT, CallbackContext callbackcontext = CallbackContext::Any)
{

   pparticle->fork([=]()
   {

      auto pwaiter = ref aaa_primitive_new waiter_for_Windows_Foundation_IAsyncOperation < T >(operation, callbackcontext);

      pwaiter->wait(pred, dwMillis);

   });

}


template < typename T, typename PRED >
inline void wait_then(::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, PRED pred, unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr, CallbackContext callbackcontext = CallbackContext::Any)
{

   auto pwaiter = ref aaa_primitive_new waiter_for_Windows_Foundation_IAsyncOperation < T >(operation, callbackcontext);

   pwaiter->wait(pred, dwMillis, pstatus);

}


template < typename T >
inline T wait(::winrt::Windows::Foundation::IAsyncOperation < T > ^ operation, unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr, CallbackContext callbackcontext = CallbackContext::Any)
{

   auto pwaiter = ref aaa_primitive_new waiter_for_Windows_Foundation_IAsyncOperation < T >(operation, callbackcontext);

   return pwaiter->wait(dwMillis, pstatus);

}


template < typename T, typename T2 >
inline T wait(::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr, CallbackContext callbackcontext = CallbackContext::Any)
{

   auto pwaiter = ref aaa_primitive_new waiter_for_Windows_Foundation_IAsyncOperationWithProgress < T, T2 > (operation, callbackcontext);

   return pwaiter->wait(dwMillis, pstatus);

}


inline ::winrt::Windows::Foundation::AsyncStatus wait(::winrt::Windows::Foundation::IAsyncAction ^ action,  unsigned int dwMillis = U32_INFINITE_TIMEOUT, CallbackContext callbackcontext = CallbackContext::Any)
{

   ::winrt::Windows::Foundation::AsyncStatus status = ::winrt::Windows::Foundation::AsyncStatus::Canceled; // for time out

   auto pwaiter = ref aaa_primitive_new waiter_for_Windows_Foundation_IAsyncAction (action, callbackcontext);

   pwaiter->wait(dwMillis, &status);

   return status;

}



