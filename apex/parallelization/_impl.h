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

_AFXMT_INLINE critical_sectioncritical_section() : synchronization < HANDLE > (nullptr)
{
   int_bool bSuccess;

   bSuccess = Init();
   if (!bSuccess)
      throw ::exception(error_no_memory);
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
      throw ::exception(error_no_memory);
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
//      throw ::exception(range_error("abandoned index out of range"));
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
//      throw ::exception(range_error("signaled index out of range"));
//   return m_iEvent;
//}
//
//
//
//
//
////template <class T >
////inline synch_index_iterator::synch_index_iterator(synch_ptr_array < T > & ptra,bool bInitialLock):
////   single_lock(&ptra.m_pmutex,true)
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
//      throw ::exception(::exception(m_strErrorMessage));
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
//   void set_error_message(const ::string & strErrorMessage)
//   {
//
//      m_strErrorMessage = strErrorMessage;
//
//      m_evReady.set_event();
//
//   }
//
//
//   hold(::particle * pparticle)
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
//      ::fork(::get_app(), [&]()
//      {
//
//         try
//         {
//
//            set_value(pred());
//
//         }
//         catch(const ::exception & e)
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
//   void wait(::pointer<THREAD>& pthread, const duration & duration = ::duration::infinite())
//   {
//
//      ::duration tickStart = ::duration::now();
//
//      while(pthread.is_set() && pthread->task_get_run() && ::task_get_run())
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
//            if((::duration::now() - tickStart) > duration.get_total_milliseconds())
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
//         if(!::task_get_run() || !pred())
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
//   return ::task_get_run();
//
//}
//
//
//
//
//
//
////inline thread_parameter::thread_parameter(const object * psimpleobject)
////{
////
////   m_psimpleobject = (object *)psimpleobject;
////
////   m_psimpleobject->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
////
////}
//
//
//
//


template < typename PRED >
auto sync_predicate(void (* pfnBranch )(::matter * pobjectTask, enum_priority), PRED pred, ::duration durationTimeout, enum_priority epriority)
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
//void async_predicate(void (* pfnBranch )(::matter * pobjectTask, enum_priority), PRED pred, enum_priority epriority)
//{
//
//   auto pobjectTask = __task_procedure(pred);
//
//   pfnBranch(pobjectTask, epriority);
//
//}
//
//
//inline ::thread* get_task(itask_t idthread)
//{
//
//   return (::thread*) psystem->get_task(idthread);
//
//}
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
//   ::pointer<::layered>   m_pobject;
//   T                       m_t;
//   bool                    m_bInitialized = false;
//   manual_reset_event      m_evReady;
//   string                  m_strErrorMessage;
//
//
//   void wait()
//   {
//
//      m_evReady.wait();
//
//   }
//
//   T& get()
//   {
//
//      wait();
//
//      if (m_bInitialized)
//      {
//
//         return m_t;
//
//      }
//
//      throw ::exception(::exception(m_strErrorMessage));
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
//   void set_error_message(const string& strErrorMessage)
//   {
//
//      m_strErrorMessage = strErrorMessage;
//
//      m_evReady.set_event();
//
//   }
//
//
//   hold(::particle * pparticle) :
//      m_pobject(pparticle)
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
//      __object(m_pobject)->fork([&]()
//         {
//
//            try
//            {
//
//               set_value(pred());
//
//            }
//            catch(const ::exception & e)
//            {
//
//               set_error_message(e.get_message());
//
//            }
//
//         });
//
//   }
//
//};


