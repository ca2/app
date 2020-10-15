#include "framework.h"
#include "acme/platform/static_start.h"


#undef new


critical_section * update_notification_task::g_pcs = nullptr;
::i64_map < __pointer(update_notification_task) > * update_notification_task::g_pmap = nullptr;
bool update_notification_task::g_bDestroyAll = false;


update_notification_task::update_notification_task()
{

   defer_create_mutex();

}


update_notification_task::~update_notification_task()
{

}


::estatus update_notification_task::run()
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

      system_call_update(m_iUpdate);

      if(m_bModified)
      {

         continue;

      }

      ::Sleep(iPollMillis);

   }

   return ::success;

}


void update_notification_task::notify()
{

   m_elementa.call_update(m_iUpdate);

}


__pointer(update_notification_task) & update_notification_task::task(::i64 iUpdate)
{

   cslock sl(g_pcs);

   if(!g_pmap)
   {

      g_pmap = new i64_map < __pointer(update_notification_task) >;

   }

   return g_pmap->operator[](iUpdate);

}


void update_notification_task::add(::element * pelement)
{

   sync_lock sl(mutex());

   if(m_elementa.is_empty())
   {

      if(should_poll(poll_millis()))
      {

         os_fork();

      }

   }

   m_elementa.add_item(pelement);

}


void update_notification_task::remove(::element * pelement)
{

   sync_lock sl(mutex());

   m_elementa.remove(pelement);

}


void update_notification_task::remove(::i64 iUpdate, ::element * pelement)
{

   cslock sl(g_pcs);

   auto & ptask = update_notification_task::task(iUpdate);

   ptask->remove(pelement);

//   if(ptask->m_elementa.is_empty())
//   {
//
//      g_pmap->remove_key(ptask->m_iUpdate);
//
//      if(g_pmap->is_empty())
//      {
//
//         auto pmap = g_pmap;
//
//         g_pmap = nullptr;
//
//         delete pmap;
//
//         if(g_bDestroyAll)
//         {
//
//            ::acme::del(g_pcs);
//
//         }
//
//      }
//
//   }

}


void update_notification_task::set_modified(::i64 iUpdate)
{

   cslock sl(::update_notification_task::g_pcs);

   auto & ptask = update_notification_task::task(iUpdate);

   if(ptask)
   {

      ptask->m_bModified = true;

      if(!ptask->should_poll(ptask->poll_millis()))
      {

         ptask->os_fork();

      }

   }

}


void update_notification_task::post_destroy_all()
{

   cslock sl(g_pcs);

   if(::is_null(g_pmap))
   {

      return;

   }

   g_bDestroyAll = true;

}


void update_notification_task::add(::i64 iUpdate, ::element * pelement)
{

   cslock sl(g_pcs);

   auto & ptask = task(iUpdate);

   if(!ptask || ptask->is_ending())
   {

      ptask = new update_notification_task();

      ptask->m_iUpdate = iUpdate;

      ptask->m_iMillisSleep = os_get_system_update_poll_time(iUpdate);

   }

   ptask->add(pelement);

}



