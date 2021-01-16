#include "framework.h"
#include "acme/platform/static_start.h"


namespace promise
{


#undef new


   //handler::handler(const ::id &id)
   //{

   //   m_id = id;

   //   m_iUpdateSerial = -1;

   //}


   handler::handler(::promise::handler * pbacking, const ::id &id) :
           m_pbacking(pbacking)
   {

      m_id = id;

      m_iUpdateSerial = -1;

   }


   handler::~handler()
   {

   }


#ifdef DEBUG


   i64 handler::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 handler::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 handler::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::release(OBJ_REF_DBG_ARGS);

   }


#endif


   ::e_status handler::run()
   {

      auto ptask = ::get_task();

      auto psubject = __new(subject(this));

      while (!::promise::handler::g_bDestroyAll && ptask->thread_get_run())
      {

         process(psubject);

         //if (m_iUpdateSerial < 0)
//         {
//
//            m_pbacking->process_subject(m_id);
//
//         }

//         if (m_bModified)
//         {
//
//            m_bModified = false;
//
//            try
//            {
//
//               notify();
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }

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

         //m_psource->apply_update(m_id);

         //if (m_bModified)
         //{

//            continue;

  //       }

         ::sleep(iPollMillis);

      }

      return ::success;

   }


   ::promise::context * handler::context(::matter *pmatter)
   {

      sync_lock sl(mutex());

      auto & pcontext = m_mattercontext[pmatter];

      if (!pcontext)
      {

         pcontext = __new(::promise::context);

      }

      return pcontext;

   }


   void handler::deliver()
   {

      sync_lock sl(mutex());

      for (auto &pair : m_mattercontext)
      {

         auto &pmatter = pair.m_element1;

         auto &pcontext = pair.m_element2;

         if (!pcontext)
         {

            pcontext = __new(::promise::context);

         }

         if (pcontext->m_bFork)
         {

            ::task::launch(__new(subject(this, pcontext, pmatter)));

         }
         else
         {

            ::promise::subject subject(this, pcontext, pmatter);

            e_id eid = (e_id) m_id.i64();

            m_pbacking->process(&subject);

         }

      }

   }


   void handler::process(const ::action_context &actioncontext)
   {

      ::promise::subject subject(m_id, actioncontext);

      m_pbacking->process(&subject);

   }


   void handler::process()
   {

      ::promise::subject subject(this);

      m_pbacking->process(&subject);

   }


   void handler::process(const ::payload &payload)
   {

      ::promise::subject subject(this);

      subject.m_var = payload;

      m_pbacking->process(&subject);


      //for (auto& matterchange : m_matterchange)
      //{

      //   auto& pmatter = matterchange.m_element1;
      //
      //   auto& pchange = matterchange.m_element2;

      //   ::promise::subject action(this, pchange, pmatter);

      //   pchange->apply(&action);

      //}

   }


   void handler::deliver(const ::action_context &actioncontext)
   {

      for (auto &mattercontext : m_mattercontext)
      {

         auto &pmatter = mattercontext.m_element1;

         auto &pcontext = mattercontext.m_element2;

         ::promise::subject subject(this, pcontext, pmatter);

         subject.m_actioncontext = actioncontext;

         m_pbacking->process(&subject);

      }

   }


   void handler::add(::matter *pmatter, bool bForkWhenNotify)
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

      auto &pchange = m_mattercontext[pmatter];

      if (!pchange)
      {

         pchange = __new(::promise::context);

      }

      pchange->m_bFork = bForkWhenNotify;

      //if (bShouldFork)
      //{

      m_bModified = !pchange->is_up_to_date(this);

      ::task::launch(this);

      //}

   }


   void handler::remove(::matter *pmatter)
   {

      sync_lock sl(mutex());

      m_mattercontext.remove_key(pmatter);

   }


   void handler::set_modified()
   {

      sync_lock sl(mutex());

      m_bModified = true;

      m_iUpdateSerial++;

      if (!should_poll(poll_millis()))
      {

         ::task::launch(this);

      }

   }


   void handler::post_destroy_all()
   {

      sync_lock sl(mutex());

      m_mattercontext.remove_all();

   }


} // namespace promise



