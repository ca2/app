#include "framework.h"


//::pointer<::task> & branch(::pointer<::task> & ptask, ::particle * pparticle, const ::procedure & procedure)
//{
//
//   ptask = __new(predicate_task < PRED >(pparticle, pred));
//
//   ptask->branch();
//
//   return ptask;
//
//}


CLASS_DECL_ACME ::task * predicate_run(::particle * pparticle, bool bSync, const ::procedure & procedure)
{

   if (bSync)
   {

      procedure();

      return nullptr;

   }
   else
   {

      return pparticle->m_pcontext->fork(procedure);

   }

}



forking_count_task::forking_count_task(::particle * pparticle, ::pointer<object>pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, const ::function < void(index, index, index, index) > & function, ::object * pobjectTaskEnd = nullptr) :
m_pholdref(pholdref),
m_function(function),
m_iOrder(iOrder),
m_iIndex(iIndex),
m_iScan(iScan),
m_iCount(iCount),
m_pobjectTaskEnd(pobjectTaskEnd)
{
   construct();
   initialize(pparticle);
}

forking_count_task::forking_count_task(::particle * pparticle, index iOrder, index iIndex, ::count iScan, ::count iCount, cosnt ::function < void(index, index, index, index) > & function, ::object * pobjectTaskEnd = nullptr) :
m_function(function),
m_iOrder(iOrder),
m_iIndex(iIndex),
m_iScan(iScan),
m_iCount(iCount),
m_pobjectTaskEnd(pobjectTaskEnd)
{
   construct();
   initialize(pparticle);
}


void forking_count_task::construct()
{

   m_uThreadAffinityMask = (::uptr) translate_processor_affinity((int) m_iOrder);

}


forking_count_task::~forking_count_task()
{

}

void forking_count_task::run() override
{

try
{

m_function(m_iOrder, m_iIndex, m_iCount, m_iScan);

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

//return ::success;

}


CLASS_DECL_ACME void fork_count(::particle * pobjectParent, ::count iCount, const ::function < void(index, index, index, index) > & function, const ::procedure & procedureCompletion, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_task() != nullptr && ::get_task()->m_bAvoidProcedureFork)
   {

      iAffinityOrder = 1;

   }

   ::count cScan = maximum(1, minimum(iCount - iStart, iAffinityOrder));

   auto pcounter = __new(::counter(cScan, procedureCompletion));

   auto ptask = ::get_task();

   for (index iOrder = 0; iOrder < cScan; iOrder++)
   {

      auto ppredtask = __new(forking_count_task < PRED >(pparticleParent, iOrder, iOrder + iStart, cScan, iCount, pred));

      //if (::is_set(ptask))
      //{

      //   ptask->add_reference(ppredtask);

      //}

      ppredtask->m_pcounter = pcounter;

      ppredtask->branch();

   }

   //return pcounter;

}
