// This is apex API library.
//
//
//
//
//
//
//
//

// Inlines for AFXMT.H

#pragma once

#ifdef _AFXMT_INLINE

_AFXMT_INLINE int_bool semaphore::Unlock()
{ return Unlock(1, nullptr); }

_AFXMT_INLINE int_bool CEvent::SetEvent()
{ ASSERT(m_hObject != nullptr); return ::SetEvent(m_hObject); }
_AFXMT_INLINE int_bool CEvent::PulseEvent()
{ ASSERT(m_hObject != nullptr); return ::PulseEvent(m_hObject); }
_AFXMT_INLINE int_bool CEvent::ResetEvent()
{ ASSERT(m_hObject != nullptr); return ::ResetEvent(m_hObject); }

_AFXMT_INLINE CSingleLock::~CSingleLock()
{ Unlock(); }
_AFXMT_INLINE int_bool CSingleLock::IsLocked()
{ return m_bAcquired; }

_AFXMT_INLINE int_bool CMultiLock::IsLocked(::u32 dwObject)
{
   ASSERT(dwObject < m_dwCount);
   return m_bLockedArray[dwObject];
}

_AFXMT_INLINE int_bool critical_section::Init()
{
   __try
   {
      ::InitializeCriticalSection(&m_sect);
   }
   __except(STATUS_NO_MEMORY == GetExceptionCode())
   {
      return false;
   }

   return true;
}

_AFXMT_INLINE critical_sectioncritical_section() : synchronization_object < HANDLE > (nullptr)
{
   int_bool bSuccess;

   bSuccess = Init();
   if (!bSuccess)
      __throw(error_no_memory);
}

_AFXMT_INLINE critical_section::operator CRITICAL_SECTION*()
{ return (CRITICAL_SECTION*) &m_sect; }
_AFXMT_INLINE critical_section::~critical_section()
{ ::DeleteCriticalSection(&m_sect); }
_AFXMT_INLINE int_bool critical_section::Lock()
{
   __try
   {
      ::EnterCriticalSection(&m_sect);
   }
   __except(STATUS_NO_MEMORY == GetExceptionCode())
   {
      __throw(error_no_memory);
   }
   return true;
}
_AFXMT_INLINE int_bool critical_section::Lock(::u32 tickTimeout)
{ ASSERT(tickTimeout == U32_INFINITE_TIMEOUT); (void)tickTimeout; return Lock(); }
_AFXMT_INLINE int_bool critical_section::Unlock()
{ ::LeaveCriticalSection(&m_sect); return true; }

#endif //_AFXMT_INLINE






//
//inline bool synchronization_result::abandoned() const
//{ return m_iEvent <= (::index)result_abandon0; }
//
//inline ::index synchronization_result::abandoned_index() const
//{
//   if ( !abandoned() )
//      __throw(range_error("abandoned index out of range"));
//   return -(m_iEvent + (::index)result_abandon0);
//}
//
//inline bool synchronization_result::error() const
//{ return m_eresult == result_error; }
//
//inline bool synchronization_result::bad_thread() const
//{ return m_eresult == result_bad_thread; }
//
//inline bool synchronization_result::timeout() const
//{ return m_eresult == result_timeout; }
//
//inline bool synchronization_result::signaled() const
//{ return m_iEvent >= (::index)result_event0; }
//
//inline bool synchronization_result::succeeded() const
//{
//   return signaled();
//}
//
//inline ::index synchronization_result::signaled_index() const
//{
//   if ( !signaled() )
//      __throw(range_error("signaled index out of range"));
//   return m_iEvent;
//}
//
//
//
//
//
////template <class T >
////inline synch_index_iterator::synch_index_iterator(synch_ptr_array < T > & ptra,bool bInitialLock):
////   single_lock(&ptra.m_mutex,true)
////{
////
////   m_pptra = &ptra;
//
////   init(&ptra.m_indexptra,bInitialLock);
//
////}
//
//
//
//
//
//
//
//
//
//template <typename T>
//struct hold
//{
//public:
//
//   T                    m_t;
//   bool                 m_bInitialized = false;
//   manual_reset_event   m_evReady;
//   string               m_strErrorMessage;
//
//
//   void wait()
//   {
//
//      m_evReady.wait();
//
//   }
//
//   T & get()
//   {
//
//      wait();
//
//      if(m_bInitialized)
//      {
//
//         return m_t;
//
//      }
//
//      __throw(::exception::exception(m_strErrorMessage));
//
//   }
//
//   template <typename U>
//   void set_value(const U& value)
//   {
//
//      m_t = value;
//
//      m_bInitialized = true;
//
//      m_evReady.set_event();
//
//   }
//
//   void set_error_message(const string & strErrorMessage)
//   {
//
//      m_strErrorMessage = strErrorMessage;
//
//      m_evReady.set_event();
//
//   }
//
//
//   hold(::layered * pobjectContext)
//   {
//
//   }
//
//
//   ~hold()
//   {
//
//   }
//
//
//   bool valid() const noexcept
//   {
//
//      return m_bInitialized;
//
//   }
//
//   template < typename PRED >
//   void work(PRED pred)
//   {
//
//      m_bInitialized = false;
//
//      ::fork(::get_context_application(), [&]()
//      {
//
//         try
//         {
//
//            set_value(pred());
//
//         }
//         catch(const ::exception::exception & e)
//         {
//
//            set_error_message(e->get_message());
//
//         }
//
//      });
//
//   }
//
//};
//
//
//
//namespace parallelization
//{
//
//
//   template < typename THREAD >
//   void wait(__pointer(THREAD) & pthread, const duration & duration = ::duration::infinite())
//   {
//
//      millis tickStart = millis::now();
//
//      while(pthread.is_set() && pthread->thread_get_run() && ::thread_get_run())
//      {
//
//         if(!do_events())
//         {
//
//            sleep(100_ms);
//
//         }
//
//         if(pthread.is_null())
//         {
//
//            break;
//
//         }
//
//         if(!duration.is_infinite())
//         {
//
//            if((millis::now() - tickStart) > duration.get_total_milliseconds())
//            {
//
//               return;
//
//            }
//
//         }
//
//      }
//
//      if(duration.is_infinite())
//      {
//
//         pthread.release();
//
//      }
//
//   }
//
//
//} // namespace parallelization
//
//
//template < typename PRED >
//inline bool predicate_Sleep(int iTime, PRED pred)
//{
//
//   if(iTime < 100)
//   {
//
//      sleep(100_ms);
//
//   }
//   else
//   {
//
//      iTime += 99;
//
//      iTime /= 100;
//
//      for(index i = 0; i < iTime; i++)
//      {
//
//         sleep(100_ms);
//
//         if(!::thread_get_run() || !pred())
//         {
//
//            break;
//
//         }
//
//      }
//
//   }
//
//   return ::thread_get_run();
//
//}
//
//
//
//
//
//
////inline thread_parameter::thread_parameter(const context_object * psimpleobject)
////{
////
////   m_psimpleobject = (context_object *)psimpleobject;
////
////   m_psimpleobject->add_ref(OBJ_REF_DBG_ARGS);
////
////}
//
//
//
//


template < typename PRED >
auto sync_predicate(void (* pfnBranch )(::matter * pobjectTask, e_priority), PRED pred, ::duration durationTimeout, e_priority epriority)
{

   auto proutine = __sync_routine(pred);

   pfnBranch(proutine, epriority);

   proutine->sync_wait(durationTimeout);

   return proutine;

}

//
//
//template < typename PRED >
//::thread * fork(PRED pred)
//{
//
//   return ::fork(::get_task(), pred);
//
//}
//
//
//
//
//
//template < typename PRED >
//void async_predicate(void (* pfnBranch )(::matter * pobjectTask, e_priority), PRED pred, e_priority epriority)
//{
//
//   auto pobjectTask = __task_procedure(pred);
//
//   pfnBranch(pobjectTask, epriority);
//
//}
//
//
//inline ::thread* get_task(ithread_t idthread)
//{
//
//   return (::thread*) ::apex::get_system()->get_task(idthread);
//
//}
//
//
//




template <typename T>
struct hold
{
public:

   __pointer(::layered)    m_pobject;
   T                       m_t;
   bool                    m_bInitialized = false;
   manual_reset_event      m_evReady;
   string                  m_strErrorMessage;


   void wait()
   {

      m_evReady.wait();

   }

   T& get()
   {

      wait();

      if (m_bInitialized)
      {

         return m_t;

      }

      __throw(::exception::exception(m_strErrorMessage));

   }

   template <typename U>
   void set_value(const U& value)
   {

      m_t = value;

      m_bInitialized = true;

      m_evReady.set_event();

   }

   void set_error_message(const string& strErrorMessage)
   {

      m_strErrorMessage = strErrorMessage;

      m_evReady.set_event();

   }


   hold(::layered* pobjectContext) :
      m_pobject(pobjectContext)
   {

   }


   ~hold()
   {

   }


   bool valid() const noexcept
   {

      return m_bInitialized;

   }

   template < typename PRED >
   void work(PRED pred)
   {

      m_bInitialized = false;

      __object(m_pobject)->fork([&]()
         {

            try
            {

               set_value(pred());

            }
            catch(const ::exception::exception & e)
            {

               set_error_message(e.get_message());

            }

         });

   }

};


template < typename PRED >
inline ::thread_pointer object::fork(PRED pred)
{

   auto pmethod = __routine(pred);

   auto pthread = __create_new < ::thread >();

   pthread->m_pmatter = pmethod;

   pthread->m_id = typeid(pred).name();

   pthread->begin_thread();

   return pthread;

}


inline ::thread_pointer object::launch(const ::routine & routine)
{

   auto pthread = __create_new < ::thread >();

   pthread->m_pmatter = routine;

   pthread->m_id = pthread->m_pmatter->type_name();

   pthread->begin_thread();

   return pthread;

}



