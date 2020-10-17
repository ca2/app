#include "framework.h"

#include "framework.h"
#include "acme/platform/static_start.h"


#undef new


//critical_section* update::g_pcs = nullptr;
//::id_map < __pointer(update) >* update::g_pmap = nullptr;
//bool update::g_bDestroyAll = false;


update::update(const ::id& id)
{

   m_id = id;

   m_iUpdateSerial = -1;

}


update::update(::source* psource, const ::id& id) :
   m_psource(psource)
{

   m_id = id;

   m_iUpdateSerial = 0;

}


//update::update(const ::id& id) :
//   m_id(id)
//{
//
//
//   m_iUpdateSerial = 0;
//
//}





update::~update()
{

}





::estatus update::run()
{

   while (!::source::g_bDestroyAll)
   {

      if (m_bModified)
      {

         m_bModified = false;

         try
         {

            apply();

         }
         catch (...)
         {

         }

      }

      // fetch updated polling time
      int iPollMillis = poll_millis();

      if (!should_poll(iPollMillis))
      {

         break;

      }

      if (is_ending())
      {

         break;

      }

      system_update(m_id);

      if (m_bModified)
      {

         continue;

      }

      ::Sleep(iPollMillis);

   }

   return ::success;

}


::change* update::change(::matter* pmatter)
{

   auto pchange = __new(::change);

   m_matterchange[pmatter] = pchange;

   return pchange;

}


void update::apply()
{

   sync_lock sl(mutex());

   for (auto& pair : m_matterchange)
   {

      auto& pmatter = pair.m_element1;

      auto& pchange = pair.m_element2;

      if (!pchange)
      {

         pchange = __new(::change);

      }

      if (pchange->m_bFork)
      {

         start_action(__new(action(this, pchange, pmatter)));

      }
      else
      {

         ::action action(this, pchange, pmatter);

         e_id eid = (e_id) m_id.i64();

         pmatter->apply(&action);

      }

   }

}


//void update::call_update(::change * pchange)
//{
//
//   if (ptask->is_modified())
//   {
//
//      ptask->set_up_to_date();
//
//      this->update(ptask);
//
//   }
//
//}


void update::apply(const ::var& var)
{

   for (auto& matterchange : m_matterchange)
   {

      auto& pmatter = matterchange.m_element1;
      
      auto& pchange = matterchange.m_element2;

      ::action action(this, pchange, pmatter);

      pchange->apply(&action);

   }

}


void update::apply(const ::action_context& actioncontext)
{

   for (auto& matterchange : m_matterchange)
   {

      auto& pmatter = matterchange.m_element1;

      auto& pchange = matterchange.m_element2;

      ::action action(this, pchange, pmatter);

      action.m_actioncontext = actioncontext;

      pchange->apply(&action);

   }
}


void update::add(::matter* pmatter, bool bForkWhenNotify)
{

   sync_lock sl(mutex());

   bool bShouldFork = false;

   if (m_matterchange.is_empty())
   {

      if (should_poll(poll_millis()))
      {

         bShouldFork = true;

      }

   }
   if(m_iUpdateSerial >= 0)
   {

      bShouldFork = true;

   }

   auto pchange = __new(::change);

   pchange->m_bFork = bForkWhenNotify;

   m_matterchange.set_at(pmatter, pchange);

   if (bShouldFork)
   {

      m_bModified = true;

      fork_run();

   }

}


void update::remove(::matter* pmatter)
{

   sync_lock sl(mutex());

   m_matterchange.remove_key(pmatter);

}


void update::set_modified()
{

   sync_lock sl(mutex());

   m_bModified = true;

   m_iUpdateSerial++;

   if (!should_poll(poll_millis()))
   {

      fork_run();

   }

}


void update::post_destroy_all()
{

   sync_lock sl(mutex());

   m_matterchange.remove_all();

}






//update::update()
//{
//
//
//
//}
//

//update::~update()
//{
//
//}

