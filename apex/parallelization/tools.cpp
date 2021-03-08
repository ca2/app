#include "framework.h"


thread_tool::thread_tool()
{

   defer_create_mutex();

}


thread_tool::~thread_tool()
{

}


thread_group::thread_group(::object * pobject, ::e_priority epriority) :
   ::object(pobject)
{

   defer_create_mutex();

   auto estatus = initialize(pobject);

   if (!estatus)
   {

      __throw(estatus);

   }

   m_epriority                      = epriority;
   m_cCount                         = 0;
   m_cIteration                     = 0;
   m_cSpan                          = 0;

   int cOrder = get_current_process_affinity_order();

   auto iPreviousSize = m_threada.get_size();

   m_threada.set_size(cOrder);

   for(index iThread = iPreviousSize; iThread < cOrder ; iThread++)
   {

      auto & ptoolthread = m_threada[iThread];

      ptoolthread = __create_new < ::tool_thread >();

      ptoolthread->initialize_tool_thread(this);

      m_synchronizationa.add(ptoolthread->m_pevReady);

      ptoolthread->m_iThread = iThread;

      ptoolthread->m_uThreadAffinityMask = translate_processor_affinity((int) (ptoolthread->m_iThread));

      if (epriority == ::priority_none)
      {

         ptoolthread->begin(::priority_highest);

      }
      else
      {

         ptoolthread->begin(epriority);

      }

   }

}


thread_group::~thread_group()
{


}




bool thread_group::prepare(::enum_thread_op ethreadop, ::count cIteration)
{

   synchronization_lock synchronizationlock(mutex());

   for (auto & pthread : m_threada)
   {

      pthread->reset();

   }

   if (ethreadop == ::e_thread_op_predicate || ethreadop == ::e_thread_op_fork_count)
   {

      m_cCount = 0;

   }
   else
   {

      m_cCount = minimum(m_threada.get_count(), cIteration);

   }

   m_ethreadop = ethreadop;

   m_cIteration = cIteration;

   m_cSpan = maximum(1, cIteration / get_count());

   return true;

}


//bool thread_groupet::add_tool(::thread_tool * ptool)
//{
//
//   add(ptool);
//
//   ptool->m_ptoolset = this;
//
//   return true;
//
//}


bool thread_group::add_predicate(::predicate_holder_base * ppred)
{

   synchronization_lock synchronizationlock(mutex());

   if ((m_ethreadop != ::e_thread_op_predicate && m_ethreadop != ::e_thread_op_fork_count) || is_full())
   {

      return false;

   }

   if (is_full())
   {

      return false;

   }

   m_threada[m_cCount]->set_predicate(ppred);

   m_cCount++;

   return true;

}


bool thread_group::start()
{

   synchronization_lock synchronizationlock(mutex());

   if (m_cCount <= 0)
   {

      return false;

   }

   m_cSpan = m_cIteration / m_cCount;

   for (index i = 0; i < m_cCount; i++)
   {

      m_threada[i]->set_ready();

   }

   return true;

}


bool thread_group::wait()
{

   //synchronization_lock synchronizationlock(mutex());

   //if (m_cCount <= 0)
   //{

   //   return false;

   //}

   //multi_lock ml(m_cCount, m_synchronizationa);

   //synchronizationlock.unlock();

   return m_synchronizationa.wait(5_s).succeeded();

}


bool thread_group::process()
{

   start();

   wait();

   return true;

}

//bool thread_group::select_toolset(thread_group * pset)
//{
//
//   m_ptoolset = pset;
//
//   return true;
//
//}











tool_thread::tool_thread()
{

   defer_create_mutex();


}


::e_status tool_thread::initialize_tool_thread(::thread_group* pgroup)
{

   auto estatus = initialize(pgroup);

   if (!estatus)
   {

      return estatus;

   }

   m_pgroup = pgroup;

   m_iIndex = 0;
   m_pevStart = __new(manual_reset_event());
   m_pevReady = __new(manual_reset_event());

   return estatus;

}


bool tool_thread::set_predicate(::predicate_holder_base * ppred)
{

   try
   {

      ppred->m_ptoolthread = this;

      m_ppred = ppred;

      return true;

   }
   catch (...)
   {

   }

   return false;

}


::e_status tool_thread::run()
{

   try
   {

      while (thread_get_run())
      {

         if (!m_pevStart->wait(millis(300)).succeeded())
         {

            continue;

         }

         m_pevStart->ResetEvent();

         if (m_pgroup->m_ethreadop == ::e_thread_op_predicate || m_pgroup->m_ethreadop == ::e_thread_op_fork_count)
         {

            m_ppred->run();

         }
         else if (m_pgroup->m_ethreadop == ::e_thread_op_tool)
         {

            m_pitem->run();

         }

         m_pevReady->SetEvent();

      }

   }
   catch (...)
   {

   }

   m_pevReady->SetEvent();

   return ::success;

}


void tool_thread::reset()
{

   m_pevStart->ResetEvent();

   m_pevReady->ResetEvent();

}


void tool_thread::set_ready()
{

   m_pevStart->SetEvent();

}


//CLASS_DECL_APEX ::thread_group * get_thread_group(::e_priority epriority)
//{
//
//   return  ::apex::get_system()->tools(epriority);
//
//}
//
//
//CLASS_DECL_APEX ::thread_groupet * get_thread_groupet(::enum_thread_tool etool)
//{
//
//   return ::apex::get_system()->toolset(etool);
//
//}


thread_tool_item::thread_tool_item()
{

}


thread_tool_item::~thread_tool_item()
{

}


::e_status thread_tool_item::run()
{

   return ::success;

}


void thread_group::select_tool(thread_tool* ptool)
{

   m_ethreadop = ::e_thread_op_tool;

   ptool->m_itema.set_size(m_threada.get_size());

   for (index i = 0; i < thread_count(); i++)
   {

      auto& pthread = thread_at(i);

      auto& pitem = ptool->item_at(i);

      pitem = ptool->__id_create < ::thread_tool_item > (ptool->m_id);

      pitem->m_pthread = pthread;

      pitem->m_ptool = ptool;

      pthread->m_pitem = pitem;

      pthread->m_ptool = ptool;

      pthread->m_pgroup = this;

   }

   m_ptool = ptool;

}


//bool thread_groupet::prepare(::count cIteration)
//{
//
//   if (!m_pthreadtools->prepare(::thread::op_tool, cIteration))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


//predicate_set::predicate_set(::thread_group * ptools) :
//   object(ptools->get_context_application()),
//   m_pthreadtools(ptools)
//{
//
//
//}
//
//bool predicate_set::add_predicate(::predicate_holder_base * ppred)
//{
//
//   ppred->m_pset = this;
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



