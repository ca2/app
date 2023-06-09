#include "framework.h"
#include "fork.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/counter.h"
#include "acme/platform/context.h"
#include "acme/platform/node.h"
//#include "acme/primitive/primitive/function.h"


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



CLASS_DECL_ACME::task * predicate_run(::particle * pparticle, bool bSync, const ::procedure & procedure)
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


forking_count_task::forking_count_task(::particle * pparticle, ::pointer<object>pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, const ::function < void(index, index, index, index) > & function, ::object * pobjectTaskEnd) :
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


forking_count_task::forking_count_task(::particle * pparticle, index iOrder, index iIndex, ::count iScan, ::count iCount, const ::function < void(index, index, index, index) > & function, ::object * pobjectTaskEnd) :
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

   m_uThreadAffinityMask = (::uptr)acmenode()->translate_processor_affinity((int)m_iOrder);

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


