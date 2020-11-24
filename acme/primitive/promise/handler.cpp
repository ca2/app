#include "framework.h"
#include "acme/platform/static_start.h"


namespace promise
{


#undef new


   company::company(const ::id &id)
   {

      m_id = id;

      m_iUpdateSerial = -1;

   }


   company::company(::source *psource, const ::id &id) :
           m_psource(psource)
   {

      m_id = id;

      m_iUpdateSerial = -1;

   }


   company::~company()
   {

   }


#ifdef DEBUG


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


#endif


   ::estatus company::run()
   {

      auto ptask = ::get_task();

      while (!::source::g_bDestroyAll && ptask->thread_get_run())
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

         ::millis_sleep(iPollMillis);

      }

      return ::success;

   }


   ::machine *company::change(::matter *pmatter)
   {

      sync_lock sl(mutex());

      auto &pchange = m_matterchange[pmatter];

      if (!pchange)
      {

         pchange = ＿＿new(::change);

      }

      return pchange;

   }


   void company::notify()
   {

      sync_lock sl(mutex());

      for (auto &pair : m_matterchange)
      {

         auto &pmatter = pair.m_element1;

         auto &pchange = pair.m_element2;

         if (!pchange)
         {

            pchange = ＿＿new(::change);

         }

         if (pchange->m_bFork)
         {

            ::task::launch(＿＿new(subject(this, pchange, pmatter)));

         }
         else
         {

            ::subject action(this, pchange, pmatter);

            e_id eid = (e_id) m_id.i64();

            pmatter->process(&action);

         }

      }

   }


   void company::apply(const ::action_context &actioncontext)
   {

      ::subject action(m_id, actioncontext);

      m_psource->process(&action);

   }


   void company::apply()
   {

      ::subject action(this);

      m_psource->process(&action);

   }


   void company::apply(const ::var &var)
   {

      ::subject action(this);

      action.m_var = var;

      m_psource->process(&action);


      //for (auto& matterchange : m_matterchange)
      //{

      //   auto& pmatter = matterchange.m_element1;
      //
      //   auto& pchange = matterchange.m_element2;

      //   ::action action(this, pchange, pmatter);

      //   pchange->apply(&action);

      //}

   }


   void company::notify(const ::action_context &actioncontext)
   {

      for (auto &matterchange : m_matterchange)
      {

         auto &pmatter = matterchange.m_element1;

         auto &pchange = matterchange.m_element2;

         ::subject action(this, pchange, pmatter);

         action.m_actioncontext = actioncontext;

         pmatter->process(&action);

      }

   }


   void company::add(::matter *pmatter, bool bForkWhenNotify)
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

      auto &pchange = m_matterchange[pmatter];

      if (!pchange)
      {

         pchange = ＿＿new(::change);

      }

      pchange->m_bFork = bForkWhenNotify;

      //if (bShouldFork)
      //{

      m_bModified = !pchange->is_up_to_date(this);

      ::task::launch(this);

      //}

   }


   void company::remove(::matter *pmatter)
   {

      sync_lock sl(mutex());

      m_matterchange.remove_key(pmatter);

   }


   void company::set_modified()
   {

      sync_lock sl(mutex());

      m_bModified = true;

      m_iUpdateSerial++;

      if (!should_poll(poll_millis()))
      {

         ::task::launch(this);

      }

   }


   void company::post_destroy_all()
   {

      sync_lock sl(mutex());

      m_matterchange.remove_all();

   }


} // namespace promise



