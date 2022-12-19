#pragma once


#include "task.h"

//#define memory_new ACME_NEW

template < typename PRED >
class predicate_task:
   virtual public ::task
{
public:


   PRED m_predicate;


   predicate_task(::particle * pparticle, PRED pred) :
      m_predicate(pred)
   {

      m_bIsPredicate = true;

      //m_bLastingThread = false;

      //m_bFork = true;

      initialize(pparticle);


   }


   virtual ~predicate_task()
   {

   }


   void run() override
   {

      m_predicate();

      //return ::success;

   }


};


template < typename PRED >
inline auto new_predicateicate_task(::particle * pparticle, PRED pred)
{

   return __new(predicate_task < PRED > (pparticle, pred));

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
//   class ::time                                       m_timeStart;
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
//   void operator()(class ::time time, PRED pred)
//   {
//
//      m_timeStart = class ::time::now() + time;
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
//                   if(m_timeStart.elapsed() >= 0 && !m_bExecuting)
//                   {
//
//                      m_bPending = false;
//
//                      KEEP(m_bExecuting);
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


//template < typename PRED >
//CLASS_DECL_ACME ::pointer<::task>& branch(::pointer<::task> ptask, ::particle * pparticle, const ::procedure & procedure);



//template < typename PRED >
//::task * fork(::particle * pparticle, PRED pred)
//{
//
//   ::task * ptask = nullptr;
//
//   return fork(ptask, pparticle, pred);
//
//}


//template < typename PRED >
//::pointer<task>fork(PRED pred);


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








// template < typename PRED >
CLASS_DECL_ACME ::task * predicate_run(::object * pobjectParent, bool bSync, const ::procedure & procedure);


//CLASS_DECL_ACME int get_current_process_affinity_order();



//#define memory_new ACME_NEW

//
//template < typename PRED >
//::pointer<task>fork(::particle * pparticle, PRED pred)
//{
//
//   ptask = memory_new predicate_task < PRED >(pparticle, pred);
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
//::task * fork(::particle * pparticle, PRED pred, const scoped_string & strTag, int iCallStackAddUp = 0, enum_priority epriority = e_priority_normal)
//{
//
//   auto ppredtask = __new(predicate_task < PRED >(pparticle, pred));
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
//         strTag = pcallstack->xxxstack_trace();
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
//::task * opt_fork(::particle * pparticle,  PRED pred)
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
//   return fork(pparticle, pred);
//
//}


//template < typename PRED >
//inline ::pointer<::task>object::fork(PRED pred)
//{
//
//   iCallStackAddUp++;
//
//   defer_create_synchronization();
//
//   synchronous_lock synchronouslock(this->synchronization());
//
//   ptask = ::fork(ptask, this, pred, pszTag, iCallStackAddUp);
//
//   return ptask;
//
//}


//template < typename PRED >
//inline auto object::fork(PRED pred, const scoped_string & strTag, int iCallStackAddUp, enum_priority epriority)
//{
//
//   iCallStackAddUp++;
//
//   defer_create_synchronization();
//
//   synchronous_lock synchronouslock(this->synchronization());
//
//   return fork(pred, pszTag, iCallStackAddUp, epriority);
//
//}



//template < typename PRED >
//inline ::task_pointer object::defer_fork(const scoped_string & strTag, PRED pred)
//{
//
//   ::pointer<task>ptask = running(pszTag);
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
//inline void fork_release(::object * pobjectParent, pointer < T > & t)
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


//class CLASS_DECL_ACME forking_count_function :
//   virtual public particle
//{
//public:
//
//   ::function < void(index) > m_function;
//
//   struct fork_index
//   {
//
//      index       m_iOrder;
//      index       m_iIndex;
//      index       m_iScan;
//      ::count     m_cCount;
//      index       m_i;
//
//      operator index()
//      {
//
//         return m_i;
//
//      }
//
//   };
//
//   fork_index m_index;
//
//   forking_count_predicate(index iOrder, index iIndex, ::count iScan, ::count cCount, const ::function < void(index) > & function) :
//   m_predicate(function)
//   {
//
//      m_index.m_iOrder  = iOrder;
//      m_index.m_iIndex  = iIndex;
//      m_index.m_iScan   = iScan;
//      m_index.m_cCount  = cCount;
//
//   }
//
//   virtual void run() override
//   {
//
//      for (m_index.m_i = m_index.m_iIndex; m_index.m_i < m_index.m_cCount; m_index.m_i += m_index.m_iScan)
//      {
//
//         m_function(m_index);
//
//      }
//
//      //return ::success;
//
//   }
//
//};


class CLASS_DECL_ACME forking_count_task :
virtual public task
{
public:



   ::function < void(index, index, index, index) > m_function;


   index       m_iOrder;
   index       m_iIndex;
   ::count     m_iScan;
   ::count     m_iCount;

   ::pointer<object> m_pobjectTaskEnd;

   ::pointer<object> m_pholdref;


   forking_count_task(::particle * pparticle, ::pointer<object>pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, const ::function < void(index, index, index, index) > & function, ::object * pobjectTaskEnd = nullptr);

   forking_count_task(::particle * pparticle, index iOrder, index iIndex, ::count iScan, ::count iCount, const ::function < void(index, index, index, index) > & function, ::object * pobjectTaskEnd = nullptr);

   
   void construct();


   ~forking_count_task() override;

   void run() override;

};


//CLASS_DECL_ACME void fork_count(::particle * pobjectParent, ::count iCount, const ::function < void(index, index, index, index) > & function, const ::procedure & procedureCompletion, index iStart = 0);


//template < typename PRED, typename PRED_END >
//::count fork_count_end_predicate(::count iCount, PRED pred, PRED_END predEnd, class ::time time = ::time::infinite(), index iStart = 0)
//{
//
//   //ASSERT(pobjectParent != nullptr && pobjectParent->application() != nullptr);
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
//   auto pobjectTaskEnd = create_task(predEnd);
//
//   for (index iOrder = 0; iOrder < iScan; iOrder++)
//   {
//
//      auto ppredtask = __new(forking_count_task < PRED >(iOrder, iOrder + iStart, iScan, iCount, pred, pobjectTaskEnd));
//
//      ppredtask->begin();
//
//   }
//
//   return iScan;
//
//}
//

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
//   ::pointer<::object> m_pobjectTaskEnd;
//
//   forking_for_task(::particle * pparticle, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
//   ::object(pparticle),
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
//   void run()
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
//pointer_array < ::task > fork_proc(::object * pobjectParent, PRED pred, index iCount = -1)
//{
//
//   pointer_array < ::task > taskptra;
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


CLASS_DECL_ACME ::task * predicate_run(::particle * pparticle, bool bSync, const ::procedure & procedure);


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
//inline ::pointer<TYPE>& object::defer_fork(::pointer<TYPE> ptype)
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
//inline ::pointer<TYPE> object::fork(::pointer<TYPE>ptype)
//{
//
//   ::task::start(ptype);
//
//   return ptype;
//
//}



