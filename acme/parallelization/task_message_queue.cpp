// Created by camilo on 2023-11-26 20:50 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "task_message_queue.h"


#define DEEP_LOG_HERE 0


task_message_queue::task_message_queue()
{
   

#if REFERENCING_DEBUGGING


   disable_referencing_debugging();


#endif


}


task_message_queue::~task_message_queue()
{


}


message_queue * task_message_queue::get_message_queue(const ::task_index & taskindex, bool bCreate)
{

   if (!taskindex)
   {

#if DEEP_LOG_HERE >= 9

      information() << "task_message_queue::get_message_queue !task_index";

#endif

      throw ::exception(error_wrong_state);

      return nullptr;

   }

   auto psystem = system();

#if DEEP_LOG_HERE >= 9

   information() << "task_message_queue::get_message_queue psystem : (::uptr) " << (::uptr) psystem;

#endif

   critical_section_lock criticalsectionlock(&psystem->m_criticalsectionThreadStorage);

   auto pthreadstorage = psystem->_thread_storage_unlocked(taskindex);

#if DEEP_LOG_HERE >= 9

   information() << "task_message_queue::get_message_queue pthreadstorage : (::uptr) " << (::uptr) pthreadstorage;

#endif

   auto & pmessagequeue = pthreadstorage->m_pmessagequeue;

   if (!pmessagequeue)
   {

#if DEEP_LOG_HERE >= 9

      information() << "task_message_queue::get_message_queue !pmessagequeue";

#endif

      if (bCreate)
      {

         pmessagequeue = øcreate_new < message_queue>();

         pmessagequeue->m_itask = pthreadstorage->m_itask;

      }

   }

   return pmessagequeue;

}


void task_message_queue::erase_message_queue(const ::task_index & taskindex)
{

   critical_section_lock synchronouslock(&system()->m_criticalsectionThreadStorage);

   auto pthreadstorage = system()->_thread_storage_unlocked(taskindex);

   auto & pmessagequeue = pthreadstorage->m_pmessagequeue;

   pmessagequeue.release();

}


void task_message_queue::clear_message_queue(const ::task_index & taskindex)
{
   
   critical_section_lock synchronouslock(&system()->m_criticalsectionThreadStorage);

   auto pthreadstorage = system()->_thread_storage_unlocked(taskindex);

   auto & pmessagequeue = pthreadstorage->m_pmessagequeue;

   if (!pmessagequeue)
   {
   
      return;
   
   }
   
   pmessagequeue->m_messagea.erase_all();

}


::message_queue * task_message_queue::current_task_message_queue(bool bCreate)
{

   return get_message_queue(::current_task_index(), bCreate);

}


namespace platform
{


   void system::create_task_message_queue()
   {

      //g_pmutexMq = ___new mutex();

      if(m_ptaskmessagequeue)
      {

         return;

      }

      øconstruct_new(m_ptaskmessagequeue);

   }


   void system::destroy_task_message_queue()
   {

      if (!m_ptaskmessagequeue)
      {

         return;

      }

      m_ptaskmessagequeue.defer_destroy();

   }


}// namespace acme






