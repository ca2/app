// Created by camilo on 2023-11-26 20:50 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "task_message_queue.h"


task_message_queue::task_message_queue()
{
   

#if REFERENCING_DEBUGGING


   disable_referencing_debugging();


#endif


}


task_message_queue::~task_message_queue()
{


}


message_queue * task_message_queue::get_message_queue(itask_t itask, bool bCreate)
{

   if (itask == 0)
   {

      ASSERT(false);

      return nullptr;

   }

   critical_section_lock criticalsectionlock(&m_criticalsection);

   auto & pmessagequeue = m_map[itask];

   if (!pmessagequeue)
   {

      if (bCreate)
      {

         pmessagequeue = __allocate< message_queue >();

         pmessagequeue->m_itask = itask;

      }

   }

   return pmessagequeue;

}


void task_message_queue::erase_message_queue(itask_t idthread)
{

   critical_section_lock synchronouslock(&m_criticalsection);

   m_map.erase_item(idthread);

}


void task_message_queue::clear_message_queue(itask_t itask)
{
   
   critical_section_lock ml(&m_criticalsection);

   auto pmessagequeue = m_map[itask];
   
   if (pmessagequeue == nullptr)
   {
   
      return;
   
   }
   
   pmessagequeue->m_messagea.erase_all();

}


::message_queue * task_message_queue::current_task_message_queue(bool bCreate)
{

   return get_message_queue(current_itask(), bCreate);

}


namespace acid
{


   void acid::initialize_message_queue()
   {

      //g_pmutexMq = __new< mutex >();

      m_ptaskmessagequeue = __allocate< ::task_message_queue >();

   }


   void acid::finalize_message_queue()
   {

      m_ptaskmessagequeue.release();

   }


}// namespace acid






