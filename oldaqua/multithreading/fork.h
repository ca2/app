#pragma once


#undef new

#define new ACME_NEW

template < typename PRED >
class pred_thread:
   virtual public ::thread
{
public:


   PRED m_pred;


   pred_thread(::object * pobject, PRED pred) :
      m_pred(pred)
   {

      m_bLastingThread = false;

      m_bFork = true;

      auto estatus = initialize(pobject);

      if (!estatus)
      {

         __throw(::exception::exception(estatus));

      }

   }


   virtual ~pred_thread()
   {

   }


   ::estatus run() override
   {

      m_pred();

      return ::success;

   }


};


template < typename PRED >
inline auto new_pred_thread(::object * pobject, PRED pred)
{

   return __new(pred_thread < PRED > (pobject, pred));

}

class CLASS_DECL_AQUA runner :
   virtual public ::object
{
public:


   __pointer(::thread)                                 m_pthread;
   bool                                         m_bExecuting;
   bool                                         m_bPending;
   ::tick                                       m_tickStart;

   runner()
   {

      m_bExecuting = false;

      m_bPending = false;

   }

   virtual ~runner()
   {

   }

   template < typename PRED >
   void operator()(::duration duration, PRED pred)
   {

      m_tickStart = ::tick::now() + duration;

      m_bPending = true;

      auto predDelayed = [this, pred]()
             {

                while(true)
                {

                   Sleep(100);

                   if(!::thread_get_run())
                   {

                      break;

                   }

                   if(m_tickStart.elapsed() >= 0 && !m_bExecuting)
                   {

                      m_bPending = false;

                      __keep(m_bExecuting);

                      pred();

                      if(!m_bPending)
                      {

                         break;

                      }

                   }

                }

             };

      get_context_object()->defer_fork(m_pthread, predDelayed);

   }

};


template < typename PRED >
__pointer(::thread) & fork(__pointer(::thread) & pthread, ::object * pobject, PRED pred)
{

   pthread = __new(pred_thread < PRED >(pobject, pred));

   pthread->begin();

   return pthread;

}



template < typename PRED >
::thread * fork(::object * pobject, __pointer(object) pholdref, PRED pred)
{

   ::thread * pthread = nullptr;

   return fork(pthread, pobject, pholdref, pred);

}


template < typename PRED >
::thread * fork(::object * pobject, PRED pred)
{

   __pointer(::thread) pthread;

   return fork(pthread, pobject, pred);

}


template < typename PRED >
::thread * fork(PRED pred);


template < typename PRED >
inline auto object::fork(PRED pred)
{

   return ::fork(this, pred);

}



template < typename PRED >
inline auto ::object::new_pred_thread(PRED pred)
{

   return ::new_pred_thread(this, pred);

}






template < typename PRED >
::thread * pred_run(::object * pobjectParent, bool bSync, PRED pred);


CLASS_DECL_AQUA int get_current_process_affinity_order();

#undef new

#define new ACME_NEW


template < typename PRED >
::thread * & fork(::thread * & pthread, ::object * pobject, PRED pred)
{

   pthread = __new(pred_thread < PRED >(pobject, pred));

   pthread->begin();

   return pthread;

}


template < typename PRED >
::thread * fork(::object * pobject, PRED pred, const char * pszTag, int iCallStackAddUp = 0, e_priority epriority = priority_normal)
{

   auto ppredthread = __new(pred_thread < PRED >(pobject, pred));

   string strTag(pszTag);

   if (is_callstack_enabled(callstack_fork_global))
   {

      if (strTag.is_empty())
      {

         iCallStackAddUp++;

         auto pcallstack = get_callstack(callstack_fork_global, iCallStackAddUp);

         strTag = pcallstack->stack_trace();

         strTag.trim();

      }

   }

   ppredthread->set_thread_name(strTag);

   ppredthread->begin(epriority);

   return ppredthread;

}


/// optimized: forks if not forked
template < typename PRED >
::thread * opt_fork(::object * pobject,  PRED pred)
{

   if (::get_thread() != nullptr && ::get_thread()->m_bFork)
   {

      pred();

      return nullptr;

   }

   return fork(pobject, pred);

}


template < typename PRED >
inline __pointer(::thread) & object::fork(__pointer(::thread) & pthread, PRED pred, const char * pszTag, int iCallStackAddUp)
{

   iCallStackAddUp++;

   defer_create_mutex();

   sync_lock sl(mutex());

   pthread = ::fork(pthread, this, pred, pszTag, iCallStackAddUp);

   return pthread;

}


template < typename PRED >
inline auto object::fork(PRED pred, const char * pszTag, int iCallStackAddUp, e_priority epriority)
{

   iCallStackAddUp++;

   defer_create_mutex();

   sync_lock sl(mutex());

   return ::fork(this, pred, pszTag, iCallStackAddUp, epriority);

}



template < typename PRED >
inline ::thread_pointer object::defer_fork(const char * pszTag, PRED pred)
{

   __pointer(thread) pthread = running(pszTag);

   if (pthread)
   {

      return pthread;

   }

   return fork(pred, pszTag);

}


template < typename PRED >
inline auto object::opt_fork(PRED pred)
{

   return ::opt_fork(this, pred);

}


template < typename PRED >
inline ::thread_pointer object::pred_run(bool bSync, PRED pred)
{

   return ::pred_run(this, bSync, pred);

}



template < typename T >
inline void fork_release(::object * pobjectParent, __pointer(T) & t)
{

   try
   {

      T * p;

      p = t.m_p;

      p->add_ref(OBJ_REF_DBG_P_NOTE(pobjectParent, "fork_release"));

      t.release();

      ::fork(pobjectParent, [&]()
             {

                ::release(p);

             });

   }
   catch (...)
   {


   }

}


CLASS_DECL_AQUA DWORD_PTR translate_processor_affinity(int i);


template < typename PRED >
class forking_count_pred :
virtual public pred_holder_base
{
public:

   PRED m_pred;

   struct fork_index
   {

      index       m_iOrder;
      index       m_iIndex;
      index       m_iScan;
      ::count     m_cCount;
      index       m_i;

      operator index()
      {

         return m_i;

      }

   };

   fork_index m_index;

   forking_count_pred(::object * pobject, index iOrder, index iIndex, ::count iScan, ::count cCount, PRED pred) :
   ::object(pobject),
   ::pred_holder_base(pobject),
   m_pred(pred)
   {

      m_index.m_iOrder  = iOrder;
      m_index.m_iIndex  = iIndex;
      m_index.m_iScan   = iScan;
      m_index.m_cCount  = cCount;

   }

   virtual ::estatus     run() override
   {

      for (m_index.m_i = m_index.m_iIndex; m_index.m_i < m_index.m_cCount; m_index.m_i += m_index.m_iScan)
      {

         m_pred(m_index);

      }

      return ::success;

   }

};


template < typename PRED >
class forking_count_thread :
virtual public thread
{
public:



   PRED        m_pred;


   index       m_iOrder;
   index       m_iIndex;
   ::count     m_iScan;
   ::count     m_iCount;

   __pointer(object)  m_pobjectTaskEnd;

   __pointer(object)  m_pholdref;


   forking_count_thread(::object * pobject, __pointer(object) pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred, ::object * pobjectTaskEnd = nullptr) :
   ::object(pobject),
   m_pholdref(pholdref),
   m_pred(pred),
   m_iOrder(iOrder),
   m_iIndex(iIndex),
   m_iScan(iScan),
   m_iCount(iCount),
   m_pobjectTaskEnd(pobjectTaskEnd)
   {
      construct();
   }

   forking_count_thread(::object * pobject, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred, ::object * pobjectTaskEnd = nullptr) :
   ::object(pobject),
   m_pred(pred),
   m_iOrder(iOrder),
   m_iIndex(iIndex),
   m_iScan(iScan),
   m_iCount(iCount),
   m_pobjectTaskEnd(pobjectTaskEnd)
   {
      construct();
   }

   void construct()
   {

      m_dwThreadAffinityMask = translate_processor_affinity(int (m_iOrder));

   }

   virtual ~forking_count_thread()
   {

   }

   virtual ::estatus     run() override
   {

      try
      {

         m_pred(m_iOrder, m_iIndex, m_iCount, m_iScan);

      }
      catch (...)
      {

      }

      if (m_pobjectTaskEnd.is_set())
      {

         if (m_pobjectTaskEnd->get_ref_count() == 1)
         {

            m_pobjectTaskEnd->run();

         }

         m_pobjectTaskEnd.release();

      }

      return ::success;

   }

};


template < typename PRED >
auto fork_count(::object * pobjectParent, ::count iCount, PRED pred, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == nullptr || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));

   auto pcounter = __new(::counter(long(iScan)));

   auto pthread = ::get_thread();

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto ppredthread = __new(forking_count_thread < PRED >(pobjectParent, iOrder, iOrder + iStart, iScan, iCount, pred));

      if (::is_set(pthread))
      {

         pthread->add_reference(ppredthread);

      }

      ppredthread->m_pcounter = pcounter;

      ppredthread->begin();

   }

   return pcounter;

}


template < typename PRED, typename PRED_END >
::count fork_count_end_pred(::object * pobjectParent, ::count iCount, PRED pred, PRED_END predEnd, ::duration duration = ::duration::infinite(), index iStart = 0)
{

   ASSERT(pobjectParent != nullptr && pobjectParent->get_context_application() != nullptr);

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == nullptr || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));

   auto pobjectTaskEnd = create_task(predEnd);

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto ppredthread = __new(forking_count_thread < PRED >(pobjectParent, iOrder, iOrder + iStart, iScan, iCount, pred, pobjectTaskEnd));

      ppredthread->begin();

   }

   return iScan;

}


template < typename PRED >
class forking_for_thread :
virtual public thread
{
public:

   PRED     m_pred;



   index    m_iOrder;
   index    m_iIndex;
   ::count  m_iScan;
   ::count  m_iCount;

   __pointer(::object)  m_pobjectTaskEnd;

   forking_for_thread(::object * pobject, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
   ::object(pobject),
   m_pred(pred),
   m_iOrder(iOrder),
   m_iIndex(iIndex),
   m_iScan(iScan),
   m_iCount(iCount)
   {
      construct();
   }

   void construct()
   {

      m_dwThreadAffinityMask = translate_processor_affinity(int(m_iOrder));

   }

   virtual ~forking_for_thread()
   {

   }

   ::estatus     run()
   {

      for (; m_iIndex < m_iCount; m_iIndex += m_iScan)
      {

         m_pred(m_iIndex);

      }

      if (m_pobjectTaskEnd)
      {

         m_pobjectTaskEnd->m_cRun++;

         if (m_pobjectTaskEnd->m_cRun == 0)
         {

            m_pobjectTaskEnd->call();

         }

      }

      return ::success;

   }

};


template < typename PRED >
auto fork_for(::object * pobjectParent, ::count iCount, PRED pred, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == nullptr || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));

   auto pcounter = __new(::counter(iScan));

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto ppredthread = __new(forking_for_thread < PRED >(pobjectParent, iOrder, iOrder + iStart, iScan, iCount, pred));

      ppredthread->m_pcounter = pcounter;

      ppredthread->begin();

   }

   return pcounter;

}

template < typename PRED, typename PRED_END >
auto fork_for_end(::object* pobjectParent, ::count iCount, PRED pred, PRED_END predEnd, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == nullptr || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));

   auto pcounter = __new(::counter(iScan));

   auto pobjectTaskEnd = __runnable(predEnd);

   pobjectTaskEnd->m_cRun = -iScan;

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto ppredthread = __new(forking_for_thread < PRED >(pobjectParent, iOrder, iOrder + iStart, iScan, iCount, pred));

      ppredthread->m_pcounter = pcounter;

      ppredthread->m_pobjectTaskEnd = pobjectTaskEnd;

      ppredthread->begin();

   }

   return pcounter;

}



CLASS_DECL_AQUA u32 random_processor_index_generator();

template < typename PRED >
__pointer_array(::thread) fork_proc(::object * pobjectParent, PRED pred, index iCount = -1)
{

   __pointer_array(::thread) threadptra;

   int iProcCount = get_current_process_affinity_order();

   if (iCount < 0 || iCount > iProcCount)
   {

      iCount = iProcCount;

   }

   iCount = MAX(1, iCount);

   if (::get_thread() == nullptr || ::get_thread()->m_bAvoidProcFork)
   {

      iCount = 1;

   }

   for (index iProcessor = 0; iProcessor < iCount; iProcessor++)
   {

      auto ppredthread = __new(pred_thread < PRED >(pobjectParent, pred));

      ::thread * pthread = dynamic_cast < ::thread * > (ppredthread);

      pthread->m_dwThreadAffinityMask = translate_processor_affinity(random_processor_index_generator() % iProcCount);

      pthread->m_bThreadToolsForIncreasedFps = false;

      pthread->m_bAvoidProcFork = true;

      threadptra.add(pthread);

      pthread->begin();

   }

   return threadptra;

}


template < typename PRED >
::thread * pred_run(::object * pobject, bool bSync, PRED pred)
{

   if (bSync)
   {

      pred();

      return nullptr;

   }
   else
   {

      return ::fork(pobject, pred);

   }

}





template < typename PRED >
inline __pointer(::thread) & object::defer_fork(__pointer(::thread) & pthread, PRED pred)
{

   if (pthread && pthread->is_running())
   {

      return pthread;

   }

   return ::fork(pthread, this, pred);

}



