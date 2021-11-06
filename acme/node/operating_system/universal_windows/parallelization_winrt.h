#pragma once


//
//
//template < typename T >
//inline void waiter_null_result(T & t)
//{
//   t = nullptr;
//}
//
//template < >
//inline void waiter_null_result(bool & b)
//{
//   b = false;
//}
//
//template < >
//inline void waiter_null_result(unsigned int & u)
//{
//   u = 0;
//}
//
//
//template < typename T >
//class waiter_for_Windows_Foundation_IAsyncOperation
//{
//private:
//
//   manual_reset_event                                    m_event;
//   ::winrt::Windows::Foundation::IAsyncOperation < T >   m_operation;
//   ::winrt::Windows::Foundation::AsyncStatus             m_status;
//   T                                                     m_result;
//   HRESULT                                               m_hresult;
//
//
//public:
//
//
//   waiter_for_Windows_Foundation_IAsyncOperation(::winrt::Windows::Foundation::IAsyncOperation < T > operation)
//   {
//
//      m_operation             = operation;
//
//      m_operation.Completed(::winrt::Windows::Foundation::AsyncOperationCompletedHandler < T > ([this](::winrt::Windows::Foundation::IAsyncOperation < T > operation, ::winrt::Windows::Foundation::AsyncStatus status)
//      {
//
//         m_status = status;
//
//         m_event.set_event();
//
//      }));
//
//   }
//
//
//   ~waiter_for_Windows_Foundation_IAsyncOperation()
//   {
//
//   }
//
//
//   T wait(unsigned int dwMillis = INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
//   {
//
//      m_event.wait(::duration(dwMillis));
//
//      if (pstatus != nullptr)
//      {
//
//         *pstatus = m_status;
//
//      }
//
//      m_hresult = m_operation.ErrorCode();
//
//      if(m_status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
//      {
//
//         return m_operation.GetResults();
//
//      }
//      else
//      {
//
//         T t;
//
//         waiter_null_result(t);
//
//         return t;
//
//      }
//
//   }
//
//   template < typename PRED >
//   void wait(PRED pred,unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
//   {
//
//      pred(wait(dwMillis, pstatus));
//
//   }
//
//
//};
//
//
//template < typename T, typename T2 >
//class waiter_for_Windows_Foundation_IAsyncOperationWithProgress
//{
//private:
//
//   manual_reset_event                                                   m_event;
//   ::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 >  m_operation;
//   ::winrt::Windows::Foundation::AsyncStatus                            m_status;
//   T                                                                    m_result;
//
//
//public:
//
//
//   waiter_for_Windows_Foundation_IAsyncOperationWithProgress(::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > operation)
//   {
//
//      m_operation = operation;
//
//      m_operation.Completed(::winrt::Windows::Foundation::AsyncOperationWithProgressCompletedHandler < T, T2 >([this](::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > operation, ::winrt::Windows::Foundation::AsyncStatus status)
//      {
//
//         auto pholdThis = this;
//
//         m_status = status;
//
//         m_event.set_event();
//
//      }));
//
//   }
//
//
//   ~waiter_for_Windows_Foundation_IAsyncOperationWithProgress()
//   {
//
//   }
//
//
//   T wait(unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
//   {
//
//      m_event.wait(::duration(dwMillis));
//
//      if (pstatus != nullptr)
//         *pstatus = m_status;
//
//      if (m_status == ::winrt::Windows::Foundation::AsyncStatus::Completed)
//      {
//
//         return m_operation.GetResults();
//
//      }
//      else
//      {
//
//         T t;
//
//         waiter_null_result(t);
//
//         return t;
//
//      }
//
//   }
//
//};
//
//
//class waiter_for_Windows_Foundation_IAsyncAction
//{
//private:
//
//
//   manual_reset_event                                 m_event;
//   ::winrt::Windows::Foundation::IAsyncAction         m_action;
//   ::winrt::Windows::Foundation::AsyncStatus          m_status;
//
//public:
//
//
//   waiter_for_Windows_Foundation_IAsyncAction(::winrt::Windows::Foundation::IAsyncAction action)
//   {
//
//      m_action                = action;
//
//      m_action.Completed(::winrt::Windows::Foundation::AsyncActionCompletedHandler([this](::winrt::Windows::Foundation::IAsyncAction action, ::winrt::Windows::Foundation::AsyncStatus status)
//      {
//
//         auto pholdThis = this;
//
//         m_status = status;
//
//         m_event.set_event();
//
//      }));
//
//      if(m_action.Status() != ::winrt::Windows::Foundation::AsyncStatus::Started)
//      {
//
//         m_status = m_action.Status();
//
//         m_event.set_event();
//
//      }
//
//   }
//
//   ~waiter_for_Windows_Foundation_IAsyncAction()
//   {
//
//   }
//
//
//   void wait(unsigned int dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
//   {
//
//      auto pholdThis = this;
//
//      m_event.wait(::duration(dwMillis));
//
//      if(pstatus != nullptr)
//         *pstatus = m_status;
//
//   }
//
//
//};
//
//
//template < typename T, typename PRED >
//void fork_then(::object * pobject, ::winrt::Windows::Foundation::IAsyncOperation < T > operation, PRED pred, ::u32 dwMillis = U32_INFINITE_TIMEOUT)
//{
//
//   pobject->fork([=]()
//   {
//
//      waiter_for_Windows_Foundation_IAsyncOperation < T > waiter(operation);
//
//      waiter.wait(pred, dwMillis);
//
//   });
//
//}
//
//
//template < typename T, typename PRED >
//inline void wait_then(::winrt::Windows::Foundation::IAsyncOperation < T > operation, PRED pred, ::u32 dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
//{
//
//   waiter_for_Windows_Foundation_IAsyncOperation < T > waiter(operation);
//
//   waiter.wait(pred, dwMillis, pstatus);
//
//}
//
//
//template < typename T >
//inline T wait(::winrt::Windows::Foundation::IAsyncOperation < T > operation, ::u32 dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
//{
//
//   waiter_for_Windows_Foundation_IAsyncOperation < T > waiter(operation);
//
//   return waiter.wait(dwMillis, pstatus);
//
//}
//
//
//template < typename T, typename T2 >
//inline T wait(::winrt::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > operation, ::u32 dwMillis = U32_INFINITE_TIMEOUT, ::winrt::Windows::Foundation::AsyncStatus * pstatus = nullptr)
//{
//
//   waiter_for_Windows_Foundation_IAsyncOperationWithProgress < T, T2 > waiter(operation);
//
//   return waiter.wait(dwMillis, pstatus);
//
//}
//
//
//inline ::winrt::Windows::Foundation::AsyncStatus wait(::winrt::Windows::Foundation::IAsyncAction action, ::u32 dwMillis = U32_INFINITE_TIMEOUT)
//{
//
//   ::winrt::Windows::Foundation::AsyncStatus status = ::winrt::Windows::Foundation::AsyncStatus::Canceled; // for time out
//
//   waiter_for_Windows_Foundation_IAsyncAction waiter(action);
//
//   waiter.wait(dwMillis, &status);
//
//   return status;
//
//}
//
//
//
