// This is aqua API library.
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

_AFXMT_INLINE int_bool CMultiLock::IsLocked(DWORD dwObject)
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
      return FALSE;
   }

   return TRUE;
}

_AFXMT_INLINE critical_section::critical_section() : sync < HANDLE > (nullptr)
{
   int_bool bSuccess;

   bSuccess = Init();
   if (!bSuccess)
      __throw(memory_exception());
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
      __throw(memory_exception());
   }
   return TRUE;
}
_AFXMT_INLINE int_bool critical_section::Lock(DWORD tickTimeout)
{ ASSERT(tickTimeout == INFINITE); (void)tickTimeout; return Lock(); }
_AFXMT_INLINE int_bool critical_section::Unlock()
{ ::LeaveCriticalSection(&m_sect); return TRUE; }

#endif //_AFXMT_INLINE







inline bool sync_result::abandoned() const
{ return m_iEvent <= (::index)result_abandon0; }

inline ::index sync_result::abandoned_index() const
{
   if ( !abandoned() )
      __throw(range_error("abandoned index out of range"));
   return -(m_iEvent + (::index)result_abandon0);
}

inline bool sync_result::error() const
{ return m_eresult == result_error; }

inline bool sync_result::bad_thread() const
{ return m_eresult == result_bad_thread; }

inline bool sync_result::timeout() const
{ return m_eresult == result_timeout; }

inline bool sync_result::signaled() const
{ return m_iEvent >= (::index)result_event0; }

inline bool sync_result::succeeded() const
{
   return signaled();
}

inline ::index sync_result::signaled_index() const
{
   if ( !signaled() )
      __throw(range_error("signaled index out of range"));
   return m_iEvent;
}





//template <class T >
//inline synch_index_iterator::synch_index_iterator(synch_ptr_array < T > & ptra,bool bInitialLock):
//   single_lock(&ptra.m_mutex,true)
//{
//
//   m_pptra = &ptra;

//   init(&ptra.m_indexptra,bInitialLock);

//}









template <typename T>
struct hold
{
public:

   T                    m_t;
   bool                 m_bInitialized = false;
   manual_reset_event   m_evReady;
   string               m_strErrorMessage;


   void wait()
   {

      m_evReady.wait();

   }

   T & get()
   {

      wait();

      if(m_bInitialized)
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

   void set_error_message(const string & strErrorMessage)
   {

      m_strErrorMessage = strErrorMessage;

      m_evReady.set_event();

   }


   hold(::object * pobject)
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

      ::fork(::get_context_application(), [&]()
      {

         try
         {

            set_value(pred());

         }
         catch(::exception_pointer e)
         {

            set_error_message(e->get_message());

         }

      });

   }

};



namespace multithreading
{


   template < typename THREAD >
   void wait(__pointer(THREAD) & pthread, const duration & duration = ::duration::infinite())
   {

      tick tickStart = tick::now();

      while(pthread.is_set() && pthread->thread_get_run() && ::thread_get_run())
      {

         if(!do_events())
         {

            Sleep(100);

         }

         if(pthread.is_null())
         {

            break;

         }

         if(!duration.is_infinite())
         {

            if((tick::now() - tickStart) > duration.get_total_milliseconds())
            {

               return;

            }

         }

      }

      if(duration.is_infinite())
      {

         pthread.release();

      }

   }


} // namespace multithreading


template < typename PRED >
inline bool pred_Sleep(int iTime, PRED pred)
{

   if(iTime < 100)
   {

      Sleep(100);

   }
   else
   {

      iTime += 99;

      iTime /= 100;

      for(index i = 0; i < iTime; i++)
      {

         Sleep(100);

         if(!::thread_get_run() || !pred())
         {

            break;

         }

      }

   }

   return ::thread_get_run();

}






//inline thread_parameter::thread_parameter(const context_object * psimpleobject)
//{
//
//   m_psimpleobject = (context_object *)psimpleobject;
//
//   m_psimpleobject->add_ref(OBJ_REF_DBG_ARGS);
//
//}




template < typename PRED >
auto sync_pred(void (* pfnBranch )(::generic_object * pobjectTask, e_priority), PRED pred, ::duration durationTimeout, e_priority epriority)
{

   auto pobjectTask = __sync_pred(pred);

   pfnBranch(pobjectTask, epriority);

   pobjectTask->m_event.wait(durationTimeout);

   return pobjectTask;

}


template < typename PRED >
::thread * fork(PRED pred)
{

   return ::fork(::get_thread(), pred);

}





template < typename PRED >
void async_pred(void (* pfnBranch )(::generic_object * pobjectTask, e_priority), PRED pred, e_priority epriority)
{

   auto pobjectTask = __task_procedure(pred);

   pfnBranch(pobjectTask, epriority);

}


inline ::thread* get_thread(ITHREAD idthread)
{

   return (::thread*) ::get_context_system()->get_thread(idthread);

}



