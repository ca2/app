// Created by camilo on 2024-12-17 20:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "manual_reset_happening.h"
#include "synchronous_lock.h"
#include "task.h"
#include "waiting_call.h"


waiting_call_base::waiting_call_base() :
   m_ptask(::get_task())
{
   //initialize(ptask);
   //__construct(m_pmanualresethappening);


}


waiting_call_base::~waiting_call_base()
{


}


void waiting_call_base::on_start_call()
{

   if (!m_bStarted)
   {

      m_bStarted = true;

      if (m_ptask)
      {

         if (!m_ptask->is_current_task())
         {

            throw ::exception(error_wrong_state);

         }

         _synchronous_lock synchronous_lock(m_ptask->synchronization());

         m_ptask->m_waitingcallstack.add_tail(this);

      }

   }

}


void waiting_call_base::on_end_or_timeout_call(::e_status estatus)
{

   if (m_bStarted)
   {

      m_bStarted = false;

      if (m_ptask)
      {

         _synchronous_lock synchronous_lock(m_ptask->synchronization());

         m_ptask->m_waitingcallstack.erase(this);

      }

   }

}



