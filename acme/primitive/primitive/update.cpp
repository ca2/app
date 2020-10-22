#include "framework.h"
#include "acme/platform/static_start.h"


#undef new


update::update(const ::id& id)
{

   m_id = id;

   m_iUpdateSerial = -1;

}


update::update(::source* psource, const ::id& id) :
   m_psource(psource)
{

   m_id = id;

   m_iUpdateSerial = -1;

}


update::~update()
{

}


i64 update::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return ::context_object::add_ref(OBJ_REF_DBG_ARGS);

}


i64 update::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return ::context_object::dec_ref(OBJ_REF_DBG_ARGS);

}


i64 update::release(OBJ_REF_DBG_PARAMS_DEF)
{

   return ::context_object::release(OBJ_REF_DBG_ARGS);

}



::estatus update::run()
{

   while (!::source::g_bDestroyAll)
   {

      if (m_iUpdateSerial < 0)
      {

         m_psource->apply_update(m_id);

      }

      if (m_bModified)
      {

         m_bModified = false;

         try
         {

            notify();

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

      m_psource->apply_update(m_id);

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

   sync_lock sl(mutex());

   auto & pchange = m_matterchange[pmatter];

   if (!pchange)
   {
      
      pchange = __new(::change);

   }

   return pchange;

}


void update::notify()
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

         task::start(__new(action(this, pchange, pmatter)));

      }
      else
      {

         ::action action(this, pchange, pmatter);

         e_id eid = (e_id) m_id.i64();

         pmatter->apply(&action);

      }

   }

}


void update::apply(const ::action_context& actioncontext)
{

   ::action action(m_id, actioncontext);

   m_psource->apply(&action);

}


void update::apply()
{

   ::action action(this);

   m_psource->apply(&action);

}


void update::apply(const ::var& var)
{

   ::action action(this);

   action.m_var = var;

   m_psource->apply(&action);


   //for (auto& matterchange : m_matterchange)
   //{

   //   auto& pmatter = matterchange.m_element1;
   //   
   //   auto& pchange = matterchange.m_element2;

   //   ::action action(this, pchange, pmatter);

   //   pchange->apply(&action);

   //}

}


void update::notify(const ::action_context& actioncontext)
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

   //bool bShouldFork = false;

   //if (m_matterchange.is_empty())
   //{

   //   if (should_poll(poll_millis()))
   //   {

   //      bShouldFork = true;

   //   }

   //}

   //if(m_iUpdateSerial < || >>= 0)
   //{

   //   bShouldFork = true;

   //}

   auto& pchange = m_matterchange[pmatter];

   if (!pchange)
   {

      pchange = __new(::change);

   }

   pchange->m_bFork = bForkWhenNotify;

   //if (bShouldFork)
   //{

      m_bModified = !pchange->is_up_to_date(this);

      ::task::start(this);

   //}

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

      ::task::start(this);

   }

}


void update::post_destroy_all()
{

   sync_lock sl(mutex());

   m_matterchange.remove_all();

}



