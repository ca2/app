#include "framework.h"
#include "acme/platform/static_start.h"


namespace subject
{


#undef new


   //handler::handler(const ::id &id)
   //{

   //   m_id = id;

   //   m_iUpdateSerial = -1;

   //}


   handler::handler(::manager * pbacking, const ::id &id) :
           m_pbacking(pbacking)
   {

      m_id = id;

      m_iUpdateSerial = -1;

   }


   handler::~handler()
   {

   }


#ifdef _DEBUG


   i64 handler::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 handler::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 handler::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   ::e_status handler::run()
   {

      auto ptask = ::get_task();

      auto psubject = __new(subject(this));

      while (!::manager::g_bDestroyAll && ptask->task_get_run())
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


   ::context * handler::context(::matter *pmatter)
   {

      synchronous_lock synchronouslock(mutex());

      auto & pcontext = m_mattercontext[pmatter];

      if (!pcontext)
      {

         pcontext = __new(::context);

      }

      return pcontext;

   }


   void handler::deliver()
   {

      synchronous_lock synchronouslock(mutex());

      for (auto &pair : m_mattercontext)
      {

         auto &pmatter = pair.m_element1;

         auto &pcontext = pair.m_element2;

         if (!pcontext)
         {

            pcontext = __new(::context);

         }

         if (pcontext->m_papexcontext->m_bFork)
         {

            ::task::launch(__new(subject(this, pcontext, pmatter)));

         }
         else
         {

            ::subject subject(this, pcontext, pmatter);

            ::enum_id eid = (::enum_id) m_id.i64();

            m_pbacking->process(&subject);

         }

      }

   }


   void handler::process(const ::action_context &actioncontext)
   {

      ::subject subject(m_id, actioncontext);

      m_pbacking->process(&subject);

   }


   void handler::process()
   {

      ::subject subject(this);

      m_pbacking->process(&subject);

   }


   void handler::process(const ::payload & payload)
   {

      ::subject subject(this);

      subject.m_var = payload;

      m_pbacking->process(&subject);


      //for (auto& matterchange : m_matterchange)
      //{

      //   auto& pmatter = matterchange.m_element1;
      //
      //   auto& pchange = matterchange.m_element2;

      //   ::subject action(this, pchange, pmatter);

      //   pchange->apply(&action);

      //}

   }


   void handler::deliver(const ::action_context &actioncontext)
   {

      for (auto &mattercontext : m_mattercontext)
      {

         auto &pmatter = mattercontext.m_element1;

         auto &pcontext = mattercontext.m_element2;

         ::subject subject(this, pcontext, pmatter);

         subject.m_actioncontext = actioncontext;

         m_pbacking->process(&subject);

      }

   }


   void handler::add(::matter *pmatter, bool bForkWhenNotify)
   {

      synchronous_lock synchronouslock(mutex());

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

         pchange = __new(::context);

      }

      pchange->m_bFork = bForkWhenNotify;

      //if (bShouldFork)
      //{

      m_bModified = !pchange->is_up_to_date(this);

      ::task::launch(this);

      //}

   }


   void handler::erase(::matter *pmatter)
   {

      synchronous_lock synchronouslock(mutex());

      m_mattercontext.erase_key(pmatter);

   }


   void handler::set_modified()
   {

      synchronous_lock synchronouslock(mutex());

      m_bModified = true;

      m_iUpdateSerial++;

      if (!should_poll(poll_millis()))
      {

         ::task::launch(this);

      }

   }


   void handler::post_destroy_all()
   {

      synchronous_lock synchronouslock(mutex());

      m_mattercontext.erase_all();

   }


} // namespace subject



