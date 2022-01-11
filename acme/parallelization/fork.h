#pragma once


#undef new

#define new ACME_NEW

template < typename PRED >
class predicate_task:
   virtual public ::task
{
public:


   PRED m_predicate;


   predicate_task(::object * pobject, PRED pred) :
      m_predicate(pred)
   {

      m_bIsPredicate = true;

      //m_bLastingThread = false;

      //m_bFork = true;

      auto estatus = initialize(pobject);

      if (!estatus)
      {

         __throw(estatus);

      }

   }


   virtual ~predicate_task()
   {

   }


   ::e_status run() override
   {

      m_predicate();

      return ::success;

   }


};


template < typename PRED >
inline auto new_predicateicate_task(::object * pobject, PRED pred)
{

   return __new(predicate_task < PRED > (pobject, pred));

}

//class CLASS_DECL_ACME runner :
//   virtual public ::object
//{
//public:
//
//
//   ::task_pointer                          m_ptask;
//   bool                                         m_bExecuting;
//   bool                                         m_bPending;
//   ::duration                                       m_durationStart;
//
//   runner()
//   {
//
//      m_bExecuting = false;
//
//      m_bPending = false;
//
//   }
//
//   virtual ~runner()
//   {
//
//   }
//
//
//   template < typename PRED >
//   void operator()(::duration duration, PRED pred)
//   {
//
//      m_durationStart = ::duration::now() + duration;
//
//      m_bPending = true;
//
//      auto predDelayed = [this, pred]()
//             {
//
//                while(true)
//                {
//
//                   sleep(100_ms);
//
//                   if(!::task_get_run())
//                   {
//
//                      break;
//
//                   }
//
//                   if(m_durationStart.elapsed() >= 0 && !m_bExecuting)
//                   {
//
//                      m_bPending = false;
//
//                      __keep(m_bExecuting);
//
//                      pred();
//
//                      if(!m_bPending)
//                      {
//
//                         break;
//
//                      }
//
//                   }
//
//                }
//
//             };
//
//      __object(this)->start(m_ptask, predDelayed);
//
//   }
//
//};


template < typename PRED >
__pointer(::task) & branch(__pointer(::task) & ptask, ::object * pobject, PRED pred)
{

   ptask = __new(predicate_task < PRED >(pobject, pred));

   ptask->branch();

   return ptask;

}



//template < typename PRED >
//::task * fork(::object * pobject, PRED pred)
//{
//
//   ::task * ptask = nullptr;
//
//   return fork(ptask, pobject, pred);
//
//}


//template < typename PRED >
//__pointer(task) fork(PRED pred);


//template < typename PRED >
//inline ::task_pointer object::__task(PRED pred)
//{
//
//   auto ppred = __predicate(pred);
//
//   return ::task::start(pred);
//
//}


//template < typename PRED >
//inline ::task_pointer object::__task(PRED pred)
//{
//
//   auto ppred = __predicate(pred);
//
//   return ::task::start(ppred);
//
//}








template < typename PRED >
::task * predicate_run(::object * pobjectParent, bool bSync, PRED pred);


//CLASS_DECL_ACME int get_current_process_affinity_order();

#undef new

#define new ACME_NEW

//
//template < typename PRED >
//__pointer(task) fork(::object * pobject, PRED pred)
//{
//
//   ptask = new predicate_task < PRED >(pobject, pred);
//
//   ptask->begin();
//
//   ptask->release();
//
//   return ptask;
//
//}
//

//template < typename PRED >
//::task * fork(::object * pobject, PRED pred, const char * pszTag, int iCallStackAddUp = 0, enum_priority epriority = e_priority_normal)
//{
//
//   auto ppredtask = __new(predicate_task < PRED >(pobject, pred));
//
//   string strTag(pszTag);
//
//   if (is_callstack_enabled(callstack_fork_global))
//   {
//
//      if (strTag.is_empty())
//      {
//
//         iCallStackAddUp++;
//
//         auto pcallstack = get_callstack(callstack_fork_global, iCallStackAddUp);
//
//         strTag = pcallstack->stack_trace();
//
//         strTag.trim();
//
//      }
//
//   }
//
//   ppredtask->task_set_name(strTag);
//
//   ppredtask->begin(epriority);
//
//   return ppredtask;
//
//}


///// optimized: forks if not forked
//template < typename PRED >
//::task * opt_fork(::object * pobject,  PRED pred)
//{
//
//   if (::get_task() != nullptr && ::get_task()->m_bFork)
//   {
//
//      pred();
//
//      return nullptr;
//
//   }
//
//   return fork(pobject, pred);
//
//}


//template < typename PRED >
//inline __pointer(::task) object::fork(PRED pred)
//{
//
//   iCallStackAddUp++;
//
//   defer_create_mutex();
//
//   synchronous_lock synchronouslock(mutex());
//
//   ptask = ::fork(ptask, this, pred, pszTag, iCallStackAddUp);
//
//   return ptask;
//
//}


//template < typename PRED >
//inline auto object::fork(PRED pred, const char * pszTag, int iCallStackAddUp, enum_priority epriority)
//{
//
//   iCallStackAddUp++;
//
//   defer_create_mutex();
//
//   synchronous_lock synchronouslock(mutex());
//
//   return fork(pred, pszTag, iCallStackAddUp, epriority);
//
//}



//template < typename PRED >
//inline ::task_pointer object::defer_fork(const char * pszTag, PRED pred)
//{
//
//   __pointer(task) ptask = running(pszTag);
//
//   if (ptask)
//   {
//
//      return ptask;
//
//   }
//
//   return fork(pred, pszTag);
//
//}
//

//template < typename PRED >
//inline auto object::opt_fork(PRED pred)
//{
//
//   return ::opt_fork(this, pred);
//
//}



//template < typename T >
//inline void fork_release(::object * pobjectParent, __pointer(T) & t)
//{
//
//   try
//   {
//
//      T * p;
//
//      p = t.m_p;
//
//      p->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(pobjectParent, "fork_release"));
//
//      t.release();
//
//      pobjectParent->fork([&]()
//             {
//
//                ::release(p);
//
//             });
//
//   }
//   catch (...)
//   {
//
//
//   }
//
//}
//


template < typename PRED >
class forking_count_predicate :
virtual public predicate_holder_base
{
public:

   PRED m_predicate;

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

   forking_count_predicate(index iOrder, index iIndex, ::count iScan, ::count cCount, PRED pred) :
   m_predicate(pred)
   {

      m_index.m_iOrder  = iOrder;
      m_index.m_iIndex  = iIndex;
      m_index.m_iScan   = iScan;
      m_index.m_cCount  = cCount;

   }

   virtual ::e_status     run() override
   {

      for (m_index.m_i = m_index.m_iIndex; m_index.m_i < m_index.m_cCount; m_index.m_i += m_index.m_iScan)
      {

         m_predicate(m_index);

      }

      return ::success;

   }

};


template < typename PRED >
class forking_count_task :
virtual public task
{
public:



   PRED        m_predicate;


   index       m_iOrder;
   index       m_iIndex;
   ::count     m_iScan;
   ::count     m_iCount;

   __pointer(object)  m_pobjectTaskEnd;

   __pointer(object)  m_pholdref;


   forking_count_task(::object * pobject, __pointer(object) pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred, ::object * pobjectTaskEnd = nullptr) :
   m_pholdref(pholdref),
   m_predicate(pred),
   m_iOrder(iOrder),
   m_iIndex(iIndex),
   m_iScan(iScan),
   m_iCount(iCount),
   m_pobjectTaskEnd(pobjectTaskEnd)
   {
      construct();
      initialize(pobject);
   }

   forking_count_task(::object * pobject, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred, ::object * pobjectTaskEnd = nullptr) :
   m_predicate(pred),
   m_iOrder(iOrder),
   m_iIndex(iIndex),
   m_iScan(iScan),
   m_iCount(iCount),
   m_pobjectTaskEnd(pobjectTaskEnd)
   {
      construct();
      initialize(pobject);
   }

   
   void construct()
   {

      m_uThreadAffinityMask = (::uptr) translate_processor_affinity((int) m_iOrder);

   }


   virtual ~forking_count_task()
   {

   }

   virtual ::e_status     run() override
   {

      try
      {

         m_predicate(m_iOrder, m_iIndex, m_iCount, m_iScan);

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

      if (m_pcounter.is_set())
      {

         (*m_pcounter)++;

      }

      return ::success;

   }

};


template < typename PRED >
auto fork_count(::object * pobjectParent, ::count iCount, PRED pred, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_task() != nullptr && ::get_task()->m_bAvoidProcedureFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = maximum(1, minimum(iCount - iStart, iAffinityOrder));

   auto pcounter = __new(::counter32(i32(iScan)));

   auto ptask = ::get_task();

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto ppredtask = __new(forking_count_task < PRED >(pobjectParent, iOrder, iOrder + iStart, iScan, iCount, pred));

      if (::is_set(ptask))
      {

         ptask->add_reference(ppredtask);

      }

      ppredtask->m_pcounter = pcounter;

      ppredtask->branch();

   }

   return pcounter;

}


template < typename PRED, typename PRED_END >
::count fork_count_end_predicate(::count iCount, PRED pred, PRED_END predEnd, ::duration duration = ::duration::infinite(), index iStart = 0)
{

   //ASSERT(pobjectParent != nullptr && pobjectParent->application() != nullptr);

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_task() == nullptr || ::get_task()->m_bAvoidProcedureFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = maximum(1, minimum(iCount - iStart, iAffinityOrder));

   auto pobjectTaskEnd = create_task(predEnd);

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto ppredtask = __new(forking_count_task < PRED >(iOrder, iOrder + iStart, iScan, iCount, pred, pobjectTaskEnd));

      ppredtask->begin();

   }

   return iScan;

}


//template < typename PRED >
//class forking_for_task :
//virtual public task
//{
//public:
//
//   PRED     m_predicate;
//
//
//
//   index    m_iOrder;
//   index    m_iIndex;
//   ::count  m_iScan;
//   ::count  m_iCount;
//
//   __pointer(::object)  m_pobjectTaskEnd;
//
//   forking_for_task(::object * pobject, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
//   ::object(pobject),
//   m_predicate(pred),
//   m_iOrder(iOrder),
//   m_iIndex(iIndex),
//   m_iScan(iScan),
//   m_iCount(iCount)
//   {
//      construct();
//   }
//
//   void construct()
//   {
//
//      m_uThreadAffinityMask = translate_processor_affinity(int(m_iOrder));
//
//   }
//
//   virtual ~forking_for_task()
//   {
//
//   }
//
//   ::e_status run()
//   {
//
//      for (; m_iIndex < m_iCount; m_iIndex += m_iScan)
//      {
//
//         m_predicate(m_iIndex);
//
//      }
//
//      if (m_pobjectTaskEnd)
//      {
//
//         m_pobjectTaskEnd->m_cRun++;
//
//         if (m_pobjectTaskEnd->m_cRun == 0)
//         {
//
//            m_pobjectTaskEnd->operator()();
//
//         }
//
//      }
//
//      return ::success;
//
//   }
//
//};


//template < typename PRED >
//auto fork_for(::object * pobjectParent, ::count iCount, PRED pred, index iStart = 0)
//{
//
//   int iAffinityOrder = get_current_process_affinity_order();
//
//   if (::get_task() == nullptr || ::get_task()->m_bAvoidProcedureFork)
//   {
//
//      iAffinityOrder = 1;
//
//   }
//
//   ::count iScan = maximum(1, minimum(iCount - iStart, iAffinityOrder));
//
//   auto pcounter = __new(::counter < ::i32 >(iScan));
//
//   for (index iOrder = 0; iOrder < iScan; iOrder++)
//   {
//
//      auto ppredtask = __new(forking_for_task < PRED >(pobjectParent, iOrder, iOrder + iStart, iScan, iCount, pred));
//
//      ppredtask->m_pcounter = pcounter;
//
//      ppredtask->begin();
//
//   }
//
//   return pcounter;
//
//}

//template < typename PRED, typename PRED_END >
//auto fork_for_end(::object* pobjectParent, ::count iCount, PRED pred, PRED_END predEnd, index iStart = 0)
//{
//
//   int iAffinityOrder = get_current_process_affinity_order();
//
//   if (::get_task() == nullptr || ::get_task()->m_bAvoidProcedureFork)
//   {
//
//      iAffinityOrder = 1;
//
//   }
//
//   ::count iScan = maximum(1, minimum(iCount - iStart, iAffinityOrder));
//
//   auto pcounter = __new(::counter < ::i32 > (iScan));
//
//   auto pobjectTaskEnd = __runnable(predEnd);
//
//   pobjectTaskEnd->m_cRun = -iScan;
//
//   for (index iOrder = 0; iOrder < iScan; iOrder++)
//   {
//
//      auto ppredtask = __new(forking_for_task < PRED >(pobjectParent, iOrder, iOrder + iStart, iScan, iCount, pred));
//
//      ppredtask->m_pcounter = pcounter;
//
//      ppredtask->m_pobjectTaskEnd = pobjectTaskEnd;
//
//      ppredtask->begin();
//
//   }
//
//   return pcounter;
//
//}



CLASS_DECL_ACME u32 processor_index_generator();


//template < typename PRED >
//__pointer_array(::task) fork_proc(::object * pobjectParent, PRED pred, index iCount = -1)
//{
//
//   __pointer_array(::task) taskptra;
//
//   int iProcCount = get_current_process_affinity_order();
//
//   if (iCount < 0 || iCount > iProcCount)
//   {
//
//      iCount = iProcCount;
//
//   }
//
//   iCount = maximum(1, iCount);
//
//   if (::get_task() == nullptr || ::get_task()->m_bAvoidProcedureFork)
//   {
//
//      iCount = 1;
//
//   }
//
//   for (index iProcessor = 0; iProcessor < iCount; iProcessor++)
//   {
//
//      auto ppredtask = __new(predicate_task < PRED >(pobjectParent, pred));
//
//      ::task * ptask = dynamic_cast < ::task * > (ppredtask);
//
//      ptask->m_uThreadAffinityMask = translate_processor_affinity(processor_index_generator() % iProcCount);
//
//      ptask->m_bThreadToolsForIncreasedFps = false;
//
//      //ptask->m_bAvoidProcFork = true;
//
//      taskptra.add(ptask);
//
//      ptask->begin();
//
//   }
//
//   return taskptra;
//
//}


template < typename PRED >
::task * predicate_run(::object * pobject, bool bSync, PRED pred)
{

  if (bSync)
  {

     pred();

     return nullptr;

  }
  else
  {

     return pobject->fork(pred);

  }

}


//template < typename PRED >
//inline ::task_pointer & object::start(::task_pointer & ptask, PRED pred)
//{
//
//   if (ptask && ptask->is_running())
//   {
//
//      return ptask;
//
//   }
//
//   return fork(ptask, pred);
//
//}
//
//
//template < typename PRED >
//inline ::task_pointer & object::defer_fork(::task_pointer& ptask, PRED pred)
//{
//
//   if (ptask && ptask->is_running())
//   {
//
//      return ptask;
//
//   }
//
//   return fork(ptask, pred);
//
//}
//
//
//template < typename TYPE >
//inline __pointer(TYPE) & object::defer_fork(__pointer(TYPE) & ptype)
//{
//
//   if (ptype && ptype->is_running())
//   {
//
//      return ptype;
//
//   }
//
//   return fork(ptype);
//
//}


//template < typename PRED >
//inline ::task_pointer& object::fork(::task_pointer& ptask, PRED pred)
//{
//
//   ptask->m_pmatter = __predicate(pred);
//
//   return fork(ptask);
//
//}


//template < typename PRED >
//inline ::task_pointer& object::fork(::task_pointer& ptask, PRED pred)
//{
//
//   ptask->m_pmatter = __predicate(pred);
//
//   return fork(ptask);
//
//}
//
//
//template < typename TYPE >
//inline __pointer(TYPE)& object::fork(__pointer(TYPE)& ptype)
//{
//
//   ::task::start(ptype);
//
//   return ptype;
//
//}



