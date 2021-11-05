﻿#include "framework.h"
#include "acme/platform/static_start.h"


#undef new


critical_section * update::g_pcs = nullptr;
::id_map < __pointer(update) > * update::g_pmap = nullptr;
bool update::g_bDestroyAll = false;


update::update()
{

   m_iUpdateSerial = 0;

}


update::~update()
{

}


::e_status update::run()
{

   while(!g_bDestroyAll)
   {

      if(m_bModified)
      {

         m_bModified = false;

         try
         {

            notify();

         }
         catch(...)
         {

         }

      }

      // fetch updated polling time
      int iPollMillis = poll_millis();

      if(!should_poll(iPollMillis))
      {

         break;

      }

      if(is_ending())
      {

         break;

      }

      system_call_update(m_id);

      if(m_bModified)
      {

         continue;

      }

      ::sleep(iPollMillis);

   }

   return ::success;

}


void update::notify()
{

   auto psubject = new_action(m_iUpdate);

   pupdate->m_pupdatenotificationtask = this;

   pupdate->m_iSerial = m_iSerial;

   m_elementa.call_update(m_iUpdate);

}


__pointer(update) & update::task(::i64 iUpdate)
{

   cslock synchronouslock(g_pcs);

   if(!g_pmap)
   {

      g_pmap = new i64_map < __pointer(update) >;

   }

   return g_pmap->operator[](iUpdate);

}


void update::add(::matter * pmatter)
{

   synchronous_lock synchronouslock(mutex());

   if(m_elementa.is_empty())
   {

      if(should_poll(poll_millis()))
      {

         fork_run();

      }

   }

   m_elementa.add_item(pmatter);

}


void update::erase(::matter * pmatter)
{

   synchronous_lock synchronouslock(mutex());

   m_elementa.erase(pmatter);

}


void update::_erase(::i64 iUpdate, ::matter * pmatter)
{

   cslock synchronouslock(g_pcs);

   auto& ptask = task(iUpdate);

   ptask->erase(pmatter);

}


void update::_erase(::matter* pmatter)
{


   cslock synchronouslock(g_pcs);

   for (auto& ptask : g_pmap->values())
   {

      ptask->erase(pmatter);

   }
 
}


void update::set_modified(::i64 iUpdate)
{

   cslock synchronouslock(::update::g_pcs);

   auto & ptask = update::task(iUpdate);

   if(ptask)
   {

      ptask->m_bModified = true;

      ptask->m_iSerial++;

      if(!ptask->should_poll(ptask->poll_millis()))
      {

         ptask->fork_run();

      }

   }

}


void update::post_destroy_all()
{

   cslock synchronouslock(g_pcs);

   if(::is_null(g_pmap))
   {

      return;

   }

   g_bDestroyAll = true;

}


void update::_add(::i64 iUpdate, ::matter * pmatter)
{

   cslock synchronouslock(g_pcs);

   auto & ptask = task(iUpdate);

   if(!ptask || ptask->is_ending())
   {

      ptask = new update();

      ptask->m_iUpdate = iUpdate;

      ptask->m_iMillisSleep = os_get_system_update_poll_time(iUpdate);

   }

   ptask->add(pmatter);

}



