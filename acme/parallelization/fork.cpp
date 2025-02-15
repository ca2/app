#include "framework.h"
#include "fork.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/counter.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
//#include "acme/prototype/prototype/function.h"


//::pointer<::task> & branch(::pointer<::task> & ptask, ::particle * pparticle, const ::procedure & procedure)
//{
//
//   ptask = __allocate predicate_task < PRED > (pparticle, pred);
//
//   ptask->branch();
//
//   return ptask;
//
//}



CLASS_DECL_ACME::task * predicate_run(::particle * pparticle, bool bSync, const ::procedure & procedure)
{

   if (bSync)
   {

      procedure();

      return nullptr;

   }
   else
   {

      return pparticle->m_papplication->fork(procedure);

   }

}


forking_count_task::forking_count_task(::particle * pparticle, ::pointer<object>pholdref, ::collection::index iOrder, ::collection::index iIndex, ::collection::count iScan, ::collection::count iCount, const ::function < void(::collection::index, ::collection::index, ::collection::index, ::collection::index) > & function, ::object * pobjectTaskEnd) :
   m_pholdref(pholdref),
   m_function(function),
   m_iOrder(iOrder),
   m_iIndex(iIndex),
   m_iScan(iScan),
   m_iCount(iCount),
   m_pobjectTaskEnd(pobjectTaskEnd)
{

   initialize(pparticle);

   construct();

}


forking_count_task::forking_count_task(::particle * pparticle, ::collection::index iOrder, ::collection::index iIndex, ::collection::count iScan, ::collection::count iCount, const ::function < void(::collection::index, ::collection::index, ::collection::index, ::collection::index) > & function, ::object * pobjectTaskEnd) :
   m_function(function),
   m_iOrder(iOrder),
   m_iIndex(iIndex),
   m_iScan(iScan),
   m_iCount(iCount),
   m_pobjectTaskEnd(pobjectTaskEnd)
{

   initialize(pparticle);

   construct();

}


void forking_count_task::construct()
{

   m_uThreadAffinityMask = (::uptr)node()->translate_processor_affinity((int)m_iOrder);

}


forking_count_task::~forking_count_task()
{

}

void forking_count_task::run()
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

      if (m_pobjectTaskEnd->reference_count() == 1)
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


