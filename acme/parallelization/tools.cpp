#include "framework.h"
#include "tools.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/node.h"


task_tool::task_tool()
{

   defer_create_synchronization();

}


task_tool::~task_tool()
{

}


task_group::task_group(::matter * pmatter, ::enum_priority epriority)
{

   defer_create_synchronization();

   //auto estatus = initialize(pparticle);

   //if (!estatus)
   //{

   //   throw ::exception(estatus);

   //}

   m_epriority                      = epriority;
   m_cCount                         = 0;
   m_cIteration                     = 0;
   m_cSpan                          = 0;

   int cOrder = node()->get_current_process_affinity_order();

   auto iPreviousSize = m_taska.get_size();

   m_taska.set_size(cOrder);

   for(::collection::index iThread = iPreviousSize; iThread < cOrder ; iThread++)
   {

      auto & ptooltask = m_taska[iThread];

      ptooltask = system()->__create_new < ::tool_task >();

      ptooltask->initialize_tool_task(this);

      m_synchronizationa.add(ptooltask->m_pevReady);

      ptooltask->m_iThread = iThread;

      ptooltask->m_uThreadAffinityMask = node()->translate_processor_affinity((int) (ptooltask->m_iThread));

      if (epriority == ::e_priority_none)
      {

         ptooltask->branch(e_parallelization_asynchronous, { .m_epriority = ::e_priority_highest });

      }
      else
      {

         ptooltask->branch(e_parallelization_asynchronous, { .m_epriority = epriority });

      }

   }

}


task_group::~task_group()
{


}


void task_group::prepare(::enum_task_op etaskop, ::collection::count cIteration)
{

   synchronous_lock synchronouslock(this->synchronization());

   for (auto & ptask : m_taska)
   {

      ptask->reset();

   }

   if (etaskop == ::e_task_op_predicate || etaskop == ::e_task_op_fork_count)
   {

      m_cCount = 0;

   }
   else
   {

      m_cCount = minimum(m_taska.get_count(), cIteration);

   }

   m_etaskop = etaskop;

   m_cIteration = cIteration;

   m_cSpan = maximum(1, cIteration / get_count());

   //return ::success;

}


//bool task_groupet::add_tool(::task_tool * ptool)
//{
//
//   add(ptool);
//
//   ptool->m_ptoolset = this;
//
//   return true;
//
//}


bool task_group::add_procedure(const ::procedure & procedure)
{

   synchronous_lock synchronouslock(this->synchronization());

   if ((m_etaskop != ::e_task_op_predicate && m_etaskop != ::e_task_op_fork_count) || is_full())
   {

      return false;

   }

   if (is_full())
   {

      return false;

   }

   m_taska[m_cCount]->set_procedure(procedure);

   m_cCount++;

   return true;

}


void task_group::set_ready_to_start()
{

   synchronous_lock synchronouslock(this->synchronization());

   if (m_cCount <= 0)
   {

      //return false;

      return;

   }

   m_cSpan = m_cIteration / m_cCount;

   ::collection::count cSuccess = 0;

   ::collection::count cFailed = 0;

   for (::collection::index i = 0; i < m_cCount; i++)
   {

      /*auto estatusTask = */ m_taska[i]->set_ready_to_start();

      //if(estatusTask.succeeded())
      //{

      //   cSuccess++;

      //}
      //else
      //{

      //   cFailed++;

      //}

   }

   //auto estatus = _003CountStatus(cSuccess, cFailed);

   //return true;

}


::e_status task_group::wait()
{

   //synchronous_lock synchronouslock(this->synchronization());

   //if (m_cCount <= 0)
   //{

   //   return false;

   //}

   //multi_lock ml(m_cCount, m_synchronizationa);

   //synchronouslock.unlock();

   return m_synchronizationa.wait(5_s) >= 0 ? ::success : ::error_wait_timeout; //.succeeded();

}


void task_group::process()
{

   set_ready_to_start();

   /*auto estatus = */ wait();

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


//bool task_group::select_toolset(task_group * pset)
//{
//
//   m_ptoolset = pset;
//
//   return true;
//
//}











tool_task::tool_task()
{

   defer_create_synchronization();


}


void tool_task::initialize_tool_task(::task_group* pgroup)
{

   //auto estatus = initialize(pgroup);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_pgroup = pgroup;

   m_iIndex = 0;
   m_pevStart = __allocate manual_reset_happening();
   m_pevReady = __allocate manual_reset_happening();

   //return estatus;

   //return ::success;

}


bool tool_task::set_procedure(const ::procedure & procedure)
{

   try
   {

      //m_ptooltask = this;

      m_procedure = procedure;

      return true;

   }
   catch (...)
   {

   }

   return false;

}


void tool_task::run()
{

   //try
   //{

   while (task_get_run())
   {

      //if (!m_pevStart->wait(300_ms).succeeded())
      m_pevStart->wait(300_ms);
      //if()
      //{

      //   continue;

      //}

      m_pevStart->reset_happening();

      if (m_pgroup->m_etaskop == ::e_task_op_predicate || m_pgroup->m_etaskop == ::e_task_op_fork_count)
      {

         m_procedure();

      }
      else if (m_pgroup->m_etaskop == ::e_task_op_tool)
      {

         m_pitem->run();

      }

      m_pevReady->set_happening();

   }

//}
//catch (...)
//{
//
//}

   m_pevReady->set_happening();

   ///return ::success;

}


void tool_task::reset()
{

   m_pevStart->reset_happening();

   m_pevReady->reset_happening();

}


void tool_task::set_ready_to_start()
{

   m_pevStart->set_happening();

//   return ::success;

}


//CLASS_DECL_ACME ::task_group * get_task_group(::enum_priority epriority)
//{
//
//   return  ::apexacmesystem()->tools(epriority);
//
//}
//
//
//CLASS_DECL_ACME ::task_groupet * get_task_groupet(::enum_task_tool etool)
//{
//
//   return ::apexacmesystem()->toolset(etool);
//
//}


task_tool_item::task_tool_item()
{

}


task_tool_item::~task_tool_item()
{

}


void task_tool_item::run()
{

   //return ::success;

}


void task_group::select_tool(task_tool* ptool)
{

   m_etaskop = ::e_task_op_tool;

   ptool->m_itema.set_size(m_taska.get_size());

   for (::collection::index i = 0; i < task_count(); i++)
   {

      auto & ptask = task_at(i);

      auto & pitem = ptool->item_at(i);

      pitem = system()->__id_create(ptool->id());

      pitem->m_ptask = ptask;

      pitem->m_ptool = ptool;

      ptask->m_pitem = pitem;

      ptask->m_ptool = ptool;

      ptask->m_pgroup = this;

   }

   m_ptool = ptool;

}


//bool task_groupet::prepare(::collection::count cIteration)
//{
//
//   if (!m_ptasktools->prepare(::task::op_tool, cIteration))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


//predicate_set::predicate_set(::task_group * ptools) :
//   matter(ptools->get_app()),
//   m_ptasktools(ptools)
//{
//
//
//}
//
//bool predicate_set::add_predicate(::predicate_holder_base * ppred)
//{
//
//   ppred->m_ppropertyset = this;
//
//   add(ppred);
//
//   return true;
//
//}
//
//
//
//



